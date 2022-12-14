#pragma once

#include "MOYFNetworking/common.h"
#include <memory>
#include <queue>

namespace MOYF {

    using MessageHandler = std::function<void(std::string)>;
    using ErrorHandler = std::function<void()>;

    class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
    public:
        using Pointer = std::shared_ptr<TCPConnection>;

        inline const std::string& GetUsername() const
        {
            return _username;
        }

        static Pointer Create(io::ip::tcp::socket&& socket)
        {
            return Pointer(new TCPConnection(std::move(socket)));
        }

        tcp::socket& Socket()
        {
            return _socket;
        }

        void Start(MessageHandler&& messageHandler, ErrorHandler&& errorHandler);
        void Post(const std::string& message);


    private:
        explicit TCPConnection(io::ip::tcp::socket&& socket);
        // wait for a new message from client
        void asyncRead();
        void onRead(boost::system::error_code ec, size_t bytesTransferred);
        void asyncWrite();
        void onWrite(boost::system::error_code ec, size_t bytesTransferred);

    private:
        tcp::socket _socket;
        std::string _username;
        std::queue<std::string> _outGoingMessages;
        io::streambuf _streamBuffer{65536};
        std::string _message = "Hello, my client.";
        MessageHandler _messageHandler;
        ErrorHandler _errorHandler;
    };
}
