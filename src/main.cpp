#include "../include/network_manager.h"
#include "../include/overlay.h"
#include "../include/render.h"
#include <windows.h>
#define BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN

int main() {
    try {
        boost::asio::io_context io_context;

        std::string server_ip = "46.191.235.182";
        unsigned short server_port = 7000;

        NetworkManager network_manager(io_context, server_ip, server_port);
        std::cout << "Waiting for packets\n";
        network_manager.startReceiving();

        io_context.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    Overlay& overlay = Overlay::getInstance();
    overlay.CreateOverlayWindow();
    overlay.RunMessageLoop();

    WSACleanup();
    return 0;
}
