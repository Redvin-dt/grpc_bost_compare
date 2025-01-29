#include "register_handler.h"
#include "http_exceptions.h"

#include <boost/json.hpp>

#include <memory>
#include <sstream>

namespace json = boost::json;

RegisterHandler::RegisterHandler(std::shared_ptr<std::map<std::string, UserData>> db) : db_(db) {}

void RegisterHandler::handleRequest(
        const http::request<http::string_body> &req,
        http::response<http::string_body> *res
) {
    std::string login;
    std::string password;
    std::string university;
    int age;
    try {
        auto body = json::parse(req.body());  
        login = static_cast<std::string> (body.at("login").as_string()); 
        password = static_cast<std::string>(body.at("password").as_string());
        university = static_cast<std::string>(body.at("university").as_string());
        age = static_cast<int>(body.at("age").as_int());
    } catch (...) {
        throw InvalidArgException("invalid body");
        // for easy impl think that code is perfect and throws error only on parse json
    }

    if (db_->find(login) != db_->end()) {
        throw AlreadyExistException("user with login: " + login + "already exists");
    }

    UserData userData = {password, university, age};
    (*db_)[login] = userData;

    std::stringstream resultBody;
    resultBody << "Successfuly registred " << login << "!\n";

    res->result(http::status::ok);
    res->set(http::field::content_type, "text/plain");
    res->body() = resultBody.str();
    
}
