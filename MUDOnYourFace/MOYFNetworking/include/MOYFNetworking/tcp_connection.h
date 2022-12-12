#pragma once

#include "MOYFNetworking/common.h"
#include <memory>

namespace MOYF {

    class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
    public:
        using Pointer = std::shared_ptr<TCPConnection>;

        static Pointer Create(boost::asio::io_context &ioContext) {
            return Pointer(new TCPConnection(ioContext));
        }

        tcp::socket &Socket() {
            return _socket;
        }

        void Start();

    private:
        explicit TCPConnection(boost::asio::io_context &ioContext);


    private:
        tcp::socket _socket;
        std::string _message{"Hello, client!"};
    };
}
