#include "MOYFNetworking/server/tcp_server.h"
#include "MOYFNetworking/server/tcp_connection.h"

namespace MOYF {
    using tcp = io::ip::tcp;

    TCPServer::TCPServer(IPV ip_version, int port) : _ipVersion(ip_version), _port(port), _acceptor(
        tcp::acceptor(
            _ioContext,
            tcp::endpoint(
                ip_version == IPV::V4 ? tcp::v4() : tcp::v6(),
                _port
            )))
    { }

    int TCPServer::Run()
    {
        try {
            StartAccept();
            _ioContext.run();
        } catch (std::exception& e) {
            print(e.what());
            return -1;
        }
        return 0;
    }

    void TCPServer::BroardCast(const std::string& message)
    {
        for (auto& connection: _connections) {
            connection->Post(message);
        }
    }

    void TCPServer::StartAccept()
    {
        // create a socket using the current io context which contains platform specific implementation;
        _dummySocket.emplace(_ioContext);
        _acceptor.async_accept(
            *_dummySocket,
            [this](const boost::system::error_code ec) {
                // move the socket into connection object for communication
                auto connection = TCPConnection::Create(std::move(*_dummySocket));

                if (OnJoin) {
                    OnJoin(connection);
                }

                _connections.insert(connection);
                if (!ec) {
                    connection->Start(
                        [this](const std::string& message) {
                            if (OnClientMessage) {
                                OnClientMessage(message);
                            }
                        },
                        [&, weak = std::weak_ptr(connection)]() {
                            if (auto shared = weak.lock();
                                shared && _connections.erase(shared)) {
                                if (OnLeave) {
                                    OnLeave(shared);
                                }
                            }
                        }

                    );
                }
                StartAccept();
            }
        );
    }


}

