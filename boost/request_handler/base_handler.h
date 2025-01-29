#pragma once
#include <boost/beast.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>

namespace beast = boost::beast;  
namespace http = beast::http;   

class BaseHandler {
public:
    BaseHandler() = default;

    virtual void handleRequest(
        const http::request<http::string_body>& req,
        http::response<http::string_body> *res    
    ) = 0;

    virtual ~BaseHandler() = default;
};
