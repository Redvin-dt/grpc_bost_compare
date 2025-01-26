#include "server.grpc.pb.h"
#include "server.pb.h"

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <unistd.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using dump::User;
using dump::ServiceTextReply;
using dump::Register;


class RegisterClient {
public:
    RegisterClient(std::shared_ptr<Channel> channel)
        : stub_(Register::NewStub(channel)) {}

    std::string Register(const std::string& user, const std::string password) {
        User request;
        request.set_login(user);
        request.set_password(password);

        ServiceTextReply reply;
        ClientContext context;
        Status status = stub_->RegisterUser(&context, request, &reply);

        if (status.ok()) {
            return reply.text();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                    << std::endl;
            return "RPC failed";
        }
    }

    std::string AutentificateUser(const std::string& user, const std::string password) {
        User request;
        request.set_login(user);
        request.set_password(password);

        ServiceTextReply reply;
        ClientContext context;
        Status status = stub_->AutentificateUser(&context, request, &reply);

        if (status.ok()) {
            return reply.text();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                    << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<dump::Register::Stub> stub_;
};

int main(int argc, char** argv) {
    RegisterClient registerClient(grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()));

    {
        std::cout << "request:" << std::endl;
        std::string reply = registerClient.Register("Bobr", "kur");
        std::cout << "Reply recievd: " << reply << std::endl;
    }

    {
        std::cout << std::endl << "request:" << std::endl;
        std::string reply = registerClient.Register("Bobr", "kur");
        std::cout << "Reply recievd: " << reply << std::endl;
    }

    {
        std::cout << std::endl << "request:" << std::endl;
        std::string reply = registerClient.AutentificateUser("Bobr", "kur");
        std::cout << "Reply recievd: " << reply << std::endl;
    }

    std::cout << std::endl << "request:" << std::endl;
    std::string reply = registerClient.AutentificateUser("Not", "found");
    std::cout << "Reply recievd: " << reply << std::endl;

    return 0;
}