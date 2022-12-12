#include "MOYFNetworking/tcp_connection.h"
#include <memory>

namespace MOYF {
    TCPConnection::TCPConnection(boost::asio::io_context &ioContext) :
            _socket(ioContext) {

    }

    void TCPConnection::Start() {
        auto strongThis = shared_from_this();
        auto dataToSend = boost::asio::buffer(_message);
        boost::asio::async_write(
                _socket,
                dataToSend,
                [strongThis](const boost::system::error_code &error, size_t bytesTransferred) {
                    if (error) {
                        print("Failed to send message");
                    } else {
                        print("Sent ", bytesTransferred, " bytes of data.");
                    }
                }
        );

        boost::asio::streambuf buffer;
        _socket.async_receive(
                buffer.prepare(512),
                [this](const boost::system::error_code &error, size_t bytesTransferred) {
                    if (!error) {
                        print("Client Disconnected Properly.");
                    } else {
                        print("Client Disconnected in Bad Way.");
                    }
                });
    }
}

