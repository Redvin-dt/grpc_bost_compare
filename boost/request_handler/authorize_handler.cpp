#include "authorize_handler.h"
#include "http_exceptions.h"

#include <boost/json.hpp>

#include <boost/json/parse.hpp>
#include <memory>
#include <sstream>

namespace json = boost::json;

AuthorizeHandler::AuthorizeHandler(std::shared_ptr<std::map<std::string, UserData>> db) : db_(db) {}

void AuthorizeHandler::handleRequest(
        const http::request<http::string_body>& req,
        http::response<http::string_body> *res    
){ 
    std::string login;
    std::string password;
    try {
        auto body = json::parse(req.body());
        login = static_cast<std::string> (body.at("login").as_string()); 
        password = static_cast<std::string>(body.at("password").as_string());
    } catch (...) {
        throw InvalidArgException("invalid body");

        // for easy impl think that code is perfect and throws error only on parse json
    }

    if (db_->find(login) == db_->end()) {
        throw NotFoundException("user with that login not found");
    }

    if (db_->at(login).password != password) {
        throw AccessDenyException("invalid login or password");
    }

    std::stringstream resultBody;
    resultBody << "Welcome " << login << "!\n";

    res->result(http::status::ok);
    res->set(http::field::content_type, "text/plain");
    res->body() = resultBody.str();
}
