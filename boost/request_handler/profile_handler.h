#pragma once
#include <base_handler.h>
#include <map>
#include <memory>
#include <boost/beast.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>

#include "user_data.h"

namespace beast = boost::beast;
namespace http = beast::http;

class ProfileHandler final : BaseHandler {
public:
    explicit ProfileHandler(std::shared_ptr<std::map<std::string, UserData>> db);

    virtual void handleRequest(
        const http::request<http::string_body>& req,
        http::response<http::string_body> *res
    ) override;

    ~ProfileHandler() override = default;
private:
    std::shared_ptr<std::map<std::string, UserData>> db_;
};
