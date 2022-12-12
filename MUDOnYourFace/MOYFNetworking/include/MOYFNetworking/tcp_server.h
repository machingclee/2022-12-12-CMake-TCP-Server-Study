#pragma once

#include "MOYFNetworking/common.h"
#include "MOYFNetworking/tcp_connection.h"


namespace MOYF {
    enum class IPV {
        V4,
        V6
    };

    class TCPServer {
    public:
        TCPServer(IPV ip_version, int port);

        int Run();

    private:
        void StartAccept();

    private:
        IPV _ipVersion;
        int _port;
        boost::asio::io_context _ioContext{};
        boost::asio::ip::tcp::acceptor _acceptor;

        std::vector<TCPConnection::Pointer> _connections{};
    };
}