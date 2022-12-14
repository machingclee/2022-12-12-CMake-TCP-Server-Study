#include "MOYFNetworking/server/tcp_server.h"
#include "boost/asio.hpp"

int port_number = 8080;

int main()
{
    MOYF::TCPServer server{MOYF::IPV::V4, port_number};
    server.OnJoin = [](MOYF::TCPConnection::Pointer& connection) {
        print(
            "User [",
            connection->GetUsername(),
            "] has join the server"
        );
    };
    server.OnLeave = [](MOYF::TCPConnection::Pointer& connection) {
        print(
            "User [",
            connection->GetUsername(),
            "] has left the server"
        );
    };
    server.OnClientMessage = [&server](const std::string& message) {
        server.BroardCast(message);
    };

    server.Run();
}
