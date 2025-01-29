#pragma once

#include <base_handler.h>

#include <map>
#include <memory>
#include <string>

class RequestFactory {
public:
    RequestFactory(std::shared_ptr<std::map<std::string, std::string>> db);
    std::shared_ptr<BaseHandler> getRequestHandler(http::request<http::string_body> req);  

private:
    std::shared_ptr<std::map<std::string, std::string>> db_;
};