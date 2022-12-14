#pragma once

#include "MOYFNetworking/common.h"
#include "tcp_connection.h"
#include <optional>
#include <functional>
#include <unordered_set>

namespace MOYF {
    enum class IPV {
        V4, V6
    };

    class TCPServer {
        using OnJoinHandler = std::function<void(TCPConnection::Pointer&)>;
        using OnLeaveHandler = std::function<void(TCPConnection::Pointer&)>;
        using OnClientMessageHandler = std::function<void(std::string)>;

    public:
        TCPServer(IPV ip_version, int port);
        int Run();
        void BroardCast(const std::string& message);
    public:
        OnJoinHandler OnJoin;
        OnLeaveHandler OnLeave;
        OnClientMessageHandler OnClientMessage;

    private:
        void StartAccept();

    private:
        IPV _ipVersion;
        int _port;
        io::io_context _ioContext{};
        io::ip::tcp::acceptor _acceptor;
        std::optional<io::ip::tcp::socket> _dummySocket;
        std::unordered_set<TCPConnection::Pointer> _connections{};
    };
}