#include "../include/network_manager.h"

using boost::asio::ip::udp;

class NetworkManager {
public:
    NetworkManager(boost::asio::io_context& io_context, const std::string& server_ip, unsigned short server_port)
        : socket_(io_context, udp::endpoint(udp::v4(), 0)),
        server_endpoint_(boost::asio::ip::address::from_string(server_ip), server_port) {
    }

    void startReceiving() {
        receiveData();
    }

private:
    void receiveData() {
        socket_.async_receive_from(
            boost::asio::buffer(receive_buffer_), server_endpoint_,
            [this](boost::system::error_code ec, std::size_t bytes_received) {
                if (!ec) {
                    processData(bytes_received);
                }
                receiveData();
            });
    }

    void processData(std::size_t bytes_received) {
        //EnemyValues enemies;
        //if (enemies.ParseFromArray(receive_buffer_.data(), bytes_received)) {
        //    updatePlayerPositions(enemies);
        //}
        //else {
        //    std::cerr << "Failed to parse Protobuf data!" << std::endl;
        //}
    }

    udp::socket socket_;
    udp::endpoint server_endpoint_;
    std::array<char, 4096> receive_buffer_;  
};
