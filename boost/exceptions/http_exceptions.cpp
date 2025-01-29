#include "http_exceptions.h"
#include <boost/beast/http/status.hpp>
#include <stdexcept>


HttpException::HttpException(http::status statusCode, std::string message) : std::runtime_error(std::move(message)), statusCode_(statusCode) {
}

http::status HttpException::getStatusCode() {
    return statusCode_;
}

NotFoundException::NotFoundException(std::string message) : HttpException(http::status::not_found, "Not found: " + message) {
}


AccessDenyException::AccessDenyException(std::string message) : HttpException(http::status::forbidden, "Access Deny: " + message) {

}

BadRequestException::BadRequestException(std::string message) : HttpException(http::status::bad_request, "Bad request: " + message) {
}


AlreadyExistException::AlreadyExistException(std::string message) : HttpException(http::status::bad_request, "Already exist: " + message) {
}


InvalidArgException::InvalidArgException(std::string message) : HttpException(http::status::bad_request, "Invalid argument: " + message) {
}

InternalErrorException::InternalErrorException(std::string message) : HttpException(http::status::internal_server_error, "Internal error: " + message) {
}

