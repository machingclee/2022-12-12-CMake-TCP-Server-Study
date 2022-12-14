#pragma once

#include "MOYFNetworking/common.h"
#include <functional>
#include <queue>

namespace MOYF {
    using MessageHandler = std::function<void(std::string)>;

    class TCPClient {
    public:
        TCPClient(const std::string& address, int port);
        void Run();
        void Stop();
        void Post(const std::string& message);

    private:
        void asyncRead();
        void onRead(boost::system::error_code ec, size_t bytesTransferred);
        void asyncWrite();
        void onWrite(boost::system::error_code ec, size_t bytesTransferred);

    public:
        MessageHandler onMessage;
    private:
        io::io_context _ioContext{};
        io::ip::tcp::socket _socket;
        io::ip::tcp::resolver::results_type _endpoints;
        io::streambuf _streamBuffer{65536};
        std::queue<std::string> _outgoingMessages{};
    };
}


