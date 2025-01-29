#pragma once

#include "profile_handler.h"
#include "http_exceptions.h"

#include <boost/json.hpp>

#include <boost/json/parse.hpp>
#include <memory>
#include <sstream>

#include "user_data.h"

namespace json = boost::json;

ProfileHandler::ProfileHandler(std::shared_ptr<std::map<std::string, UserData>> db) : db_(db) {
}

void ProfileHandler::handleRequest(
    const http::request<http::string_body> &req,
    http::response<http::string_body> *res
    ) {

    std::string login;
    std::string password;

    try {
        auto body = json::parse(req.body());
        login = static_cast<std::string> (body.at("login").as_string());
        password = static_cast<std::string>(body.at("password").as_string());
    } catch (...) {
        throw InvalidArgException("invalid body");
    }

    auto it = db_->find(login);
    if (it == db_->end()) {
        throw NotFoundException("user with login: " + login + " not found");
    }

    const UserData& userData = it->second;

    json::object responseBody;
    responseBody["login"] = login;
    responseBody["university"] = userData.university;
    responseBody["age"] = userData.age;

    res->result(http::status::ok);
    res->set(http::field::content_type, "application/json");
    res->body() = json::serialize(responseBody);
}



