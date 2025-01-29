#include "http_exceptions.h"
#include <functional>
#include <request_factory.h>

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/json.hpp>

#include <memory>
#include <map>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

void session(tcp::socket socket, RequestFactory& requestFactory)
{
    try
    {
        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        http::response<http::string_body> res;

        try {
            auto requestHandler = requestFactory.getRequestHandler(req);
            requestHandler->handleRequest(req, &res);
            res.prepare_payload();

            http::write(socket, res);
        } catch (HttpException e) {
            res.result(e.getStatusCode());
            res.set(http::field::content_type, "text/plain");
            res.body() = e.what();
            res.prepare_payload();
            std::cout << "catch erorr" << std::endl;
            http::write(socket, res);
            return;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unexpected error" << std::endl;
    }
}

int main()
{
    try
    {
        net::io_context ioc;
        tcp::acceptor acceptor(ioc, { tcp::v4(), 8080 });

        std::cout << "Server is running on http://localhost:8080/" << std::endl;

        RequestFactory requestFactory(std::make_shared<std::map<std::string, std::string>>());

        while (true)
        {
            tcp::socket socket(ioc);
            acceptor.accept(socket);
            std::thread(session, std::move(socket), std::ref(requestFactory)).detach();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal Error: " << e.what() << std::endl;

        return EXIT_FAILURE;
    }

    return 0;
}