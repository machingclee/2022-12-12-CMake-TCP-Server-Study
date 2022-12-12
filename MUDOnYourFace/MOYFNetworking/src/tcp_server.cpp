#include "MOYFNetworking/tcp_server.h"
#include "MOYFNetworking/tcp_connection.h"

namespace MOYF {
    using tcp = boost::asio::ip::tcp;

    TCPServer::TCPServer(IPV ip_version, int port)
            : _ipVersion(ip_version), _port(port),
              _acceptor(tcp::acceptor(
                      _ioContext,
                      tcp::endpoint(ip_version == IPV::V4 ? tcp::v4() : tcp::v6(), _port)
              )) {}

    int TCPServer::Run() {
        try {
            StartAccept();
            _ioContext.run();
        } catch (std::exception &e) {
            print(e.what());
            return -1;
        }
        return 0;
    }

    void TCPServer::StartAccept() {
        // this connection will be destroyed once it is out of scope
        auto connection = TCPConnection::Create(_ioContext);
        _connections.push_back(connection);
        _acceptor.async_accept(
                connection->Socket(),
                [this, connection](const boost::system::error_code ec) {
                    // capture connection by value;
                    if (!ec) {
                        connection->Start();
                    } else {
                        print(ec.what());
                    }
                    StartAccept();
                });
         
    }
}

