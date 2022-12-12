#include "boost/asio.hpp"
#include <iostream>
#include "MOYFNetworking/common.h"
#include "MOYFNetworking/tcp_server.h"


using tcp = boost::asio::ip::tcp;

int port_number = 8080;

int main() {
    MOYF::TCPServer server{MOYF::IPV::V4, port_number};
    server.Run();
}

