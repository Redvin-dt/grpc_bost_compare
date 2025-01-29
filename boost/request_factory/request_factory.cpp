#include "request_factory.h"
#include "authorize_handler.h"
#include "base_handler.h"
#include "http_exceptions.h"
#include "register_handler.h"

#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/verb.hpp>

#include <map>
#include <memory>
#include <string>

RequestFactory::RequestFactory(std::shared_ptr<std::map<std::string, std::string>> db) : db_(db) {}

std::shared_ptr<BaseHandler> RequestFactory::getRequestHandler(http::request<http::string_body> req) {
    static RegisterHandler registerHandler(db_);
    static AuthorizeHandler authorizeHandler(db_);

    if (req.method() == http::verb::put && req.target() == "/register") {
        return std::make_shared<RegisterHandler>(registerHandler);
    } else if (req.method() == http::verb::get && req.target() == "/login") {
        return std::make_shared<AuthorizeHandler>(authorizeHandler);
    } else {
        throw BadRequestException("method does not exist");
    }
}