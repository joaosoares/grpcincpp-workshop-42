#include <iostream>
#include <grpcpp/grpcpp.h>
#include <helloworld/v1/hello_world_api.grpc.pb.h>
#include <helloworld/v1/hello_world_api.pb.h>

int main()
{
  auto channel = grpc::CreateChannel("127.0.0.1:50051", grpc::InsecureChannelCredentials());
  auto stub = hello_world::v1::HelloWorldAPI::NewStub(channel);
  
  grpc::ClientContext context;
  hello_world::v1::SayHelloRequest request;
  hello_world::v1::SayHelloResponse response;
  request.set_name("42");
  
  auto status = stub->SayHello(&context, request, &response);
  if (!status.ok()) {
    std::cout << "error: " << status.error_code() << status.error_message() << std::endl;
    return 1;
  }
  std::cout << "got message from server" << response.response() << std::endl;
  return 0;
}