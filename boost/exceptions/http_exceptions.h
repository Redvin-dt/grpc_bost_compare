#pragma once
#include <boost/beast.hpp>

#include <stdexcept>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;

class HttpException : public std::runtime_error {
public:
    HttpException(http::status statusCode, std::string message);

    http::status getStatusCode();

    virtual ~HttpException() = default;
private:
    http::status statusCode_;
};

class NotFoundException : public HttpException {
public:
    NotFoundException(std::string message);
};

class AccessDenyException : public HttpException {
public:
    AccessDenyException(std::string message);
};

class BadRequestException : public HttpException {
public:
    BadRequestException(std::string message);
};

class AlreadyExistException : public HttpException {
public:
    AlreadyExistException(std::string message);
};

class InvalidArgException : public HttpException {
public:
    InvalidArgException(std::string message);
};

class InternalErrorException : public HttpException {
public:
    InternalErrorException(std::string message);
};

