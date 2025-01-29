#pragma once

#include "base_handler.h"

#include <string>
#include <map>
#include <memory>

#include "user_data.h"

class AuthorizeHandler : public BaseHandler {
public:
    AuthorizeHandler(std::shared_ptr<std::map<std::string, UserData>> db);

    virtual void handleRequest(
        const http::request<http::string_body>& req,
        http::response<http::string_body> *res    
    ) override;

    virtual ~AuthorizeHandler() = default;

private:
    std::shared_ptr<std::map<std::string, UserData>> db_;
};
