#include <iostream>
#include "MOYFNetworking/client/tcp_client.h"
#include <thread>

using namespace MOYF;

int main(int argc, char* argv[])
{
    TCPClient client{"localhost", 8080};
    client.onMessage = [](const std::string& message) {
        std::cout << message;
    };

    std::thread t{[&client]() { client.Run(); }};

    while (true) {
        std::string message;
        std::getline(
            std::cin,
            message
        );

        if (message == "\\q") {
            break;
        }

        message += "\n";
        client.Post(message);
    }

    client.Stop();
    t.join();
}
