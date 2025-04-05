#include <iostream>
#include <grpcpp/grpcpp.h>
#include <helloworld/v1/hello_world_api.grpc.pb.h>
#include <helloworld/v1/hello_world_api.pb.h>

class HelloWorldApiImpl final : public hello_world::v1::HelloWorldAPI::Service {
  grpc::Status SayHello(
    grpc::ServerContext* context,
    const hello_world::v1::SayHelloRequest& request,
    hello_world::v1::SayHelloResponse* response
  ) {
    response->set_response("Hello, " + request.name() + "!");
    return grpc::Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  HelloWorldApiImpl service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main()
{
  RunServer();
  return 0;
}