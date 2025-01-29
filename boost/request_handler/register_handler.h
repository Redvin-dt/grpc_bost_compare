#pragma once

#include "base_handler.h"

#include <map>
#include <memory>
#include <string>

class RegisterHandler : public BaseHandler {
public:
    RegisterHandler(std::shared_ptr<std::map<std::string, std::string>> db);

    virtual void handleRequest(
        const http::request<http::string_body> &req,
        http::response<http::string_body> *res
    ) override;

    virtual ~RegisterHandler() = default;
private:
    std::shared_ptr<std::map<std::string, std::string>> db_;
};