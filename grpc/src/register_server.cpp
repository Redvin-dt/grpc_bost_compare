#include "server.grpc.pb.h"
#include "server.pb.h"

#include <grpcpp/support/status.h>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <grpcpp/grpcpp.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using dump::User;
using dump::ServiceTextReply;
using dump::Register;

constexpr char* SERVICE_ADDRESS = "0.0.0.0";
constexpr int SERVICE_PORT = 50051;

class RegisterServiceImpl : public Register::Service {
    std::map<std::string, std::string> users;

    Status RegisterUser(
        ServerContext* context,
        const User* request,
        ServiceTextReply* reply
    ) override {
        
        const auto& login = request->login();
        const auto& password = request->password();

        if (users.find(login) != users.end()) {
            return Status(grpc::StatusCode::ALREADY_EXISTS, "user with that login already exist");
        }

        users[login] = password;
        std::stringstream reply_messasge;
        reply_messasge << "User with login: " << login << " successfully registred";
        reply->set_text(reply_messasge.str());
        return Status::OK;
    }

    Status AutentificateUser(
        ServerContext* context,
        const User* request,
        ServiceTextReply* reply
    ) override {
         const auto& login = request->login();
        const auto& password = request->password();

        if (users.find(login) == users.end()) {
            return Status(grpc::StatusCode::NOT_FOUND, "user with that login not found");
        }

        if (users[login] != password) {
            return Status(grpc::StatusCode::PERMISSION_DENIED, "invalid password");
        }

        std::stringstream reply_messasge;
        reply_messasge << "Welcome " << login << "!";
        reply->set_text(reply_messasge.str());
        return Status::OK;
    }
};

void RunServer(std::string address, int port) {
    std::stringstream server_address;
    server_address << address << ":" << port;

    RegisterServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address.str(), grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address.str() << std::endl;
    server->Wait();
}

int main(int argc, char* argv[]) {
    RunServer(SERVICE_ADDRESS, SERVICE_PORT);
    return 0;
}