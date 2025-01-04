#include "../include/network_manager.h"
#include <boost/bind/bind.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
#include <vector>

NetworkManager::NetworkManager(const std::string& host, const std::string& port)
	: socket(io_context, boost::asio::ip::udp::v4()), host(host), port(port) {
	start();
}

NetworkManager::~NetworkManager() {
	stop();
}

void NetworkManager::start() {
	if (is_running == true)
	{
		std::cerr << "Network manager is already running!\n";
		return;
	}

	is_running = true;

	try {
		boost::asio::ip::udp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(host, port);
		server_endpoint = *endpoints.begin();
	}
	catch (const boost::system::system_error& e) {
		std::cerr << "Error resolving host: " << e.what() << std::endl;
		return;
	}

	try {
		io_thread = std::make_unique<std::thread>([this]() { io_context.run(); });
	}
	catch (const std::exception& e) {
		std::cerr << "Error creating IO thread: " << e.what() << std::endl;
	}
}


void NetworkManager::stop() {
	if (is_running) {
		socket.close();
		io_context.stop();
		if (io_thread && io_thread->joinable()) {
			io_thread->join();
		}
		is_running = false;
	}
}

void NetworkManager::send_udp_hello() {
	if (is_running) {
		int bytes_sent = socket.send_to(boost::asio::buffer("UDP hello"), server_endpoint);
		std::cout << "[+] Sent UDP hello" << " bytes: " << bytes_sent << "\n";

	}
}

Enemies NetworkManager::receive_data() {
	try {
		boost::asio::ip::udp::endpoint sender_endpoint;
		size_t bytes_received = socket.receive_from(boost::asio::buffer(receive_buffer_), sender_endpoint);

		std::string data(receive_buffer_.data(), bytes_received);

		Enemies enemies;
		if (enemies.ParseFromString(data)) {
			return enemies;
		}
		else {
			std::cerr << "Failed to parse Protobuf data!\n";
		}
	}
	catch (const boost::system::system_error& e) {
		std::cerr << "Error during receive: " << e.what() << "\n";
	}

	return Enemies();
}
