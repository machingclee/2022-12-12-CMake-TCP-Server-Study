#include <iostream>
#include "MOYFNetworking/common.h"
#include "boost/asio.hpp"
#include <array>

using tcp = boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
    try {
        boost::asio::io_context ioContext;
        tcp::resolver resolver{ioContext};
        auto endpoints = resolver.resolve("127.0.0.1", "8080");
        tcp::socket socket{ioContext};
        boost::asio::connect(socket, endpoints);

        while (true) {
            std::array<char, 128> receivedDataBuffer{};
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(receivedDataBuffer), error);

            if (error == boost::asio::error::eof) {
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            };

            std::cout.write(receivedDataBuffer.data(), len);
        }
    } catch (std::exception &e) {
        print(e.what());
    }
}
