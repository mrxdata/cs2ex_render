#pragma once
#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <boost/asio.hpp>
#include <array>
#include <string>
#include <iostream>

using boost::asio::ip::udp;

class NetworkManager {
public:
    NetworkManager(boost::asio::io_context& io_context, const std::string& server_ip, unsigned short server_port);

    void startReceiving();

private:
    void receiveData();
    void processData(std::size_t bytes_received);

    udp::socket socket_;
    udp::endpoint server_endpoint_;
    std::array<char, 1024> receive_buffer_;
};

#endif // NETWORK_MANAGER_HPP
