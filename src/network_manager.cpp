#include "../include/network_manager.h"
#include "../include/globals.h"
#include <boost/bind/bind.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
#include <vector>

NetworkManager::NetworkManager(const std::string& host, const std::string& port)
	: socket(io_context, boost::asio::ip::udp::v4()), host(host), port(port) {
}

NetworkManager::~NetworkManager() {
	stop();
}

void NetworkManager::start() {
	if (is_running == true) {
		std::cerr << "Network manager is already running!\n";
		return;
	}

	is_running = true;

	try {
		boost::asio::ip::udp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(host, port);
		server_endpoint = *endpoints.begin();

		socket.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), std::stoi(port)));

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	catch (const boost::system::system_error& e) {
		std::cerr << "Error resolving host: " << e.what() << std::endl;
		return;
	}
}


void NetworkManager::run_io_service()
{
	try {
		io_thread = std::make_unique<std::thread>([this]() {
			std::cout << "[+] Starting io_context.run()\n";
			io_context.run();
			std::cout << "[-] io_context.run() finished\n";
			});
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
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void NetworkManager::receive_data_async() { 
	socket.async_receive_from(boost::asio::buffer(receive_buffer_), server_endpoint, 
		[this](const boost::system::error_code& error, std::size_t bytes_received) { 
			if (error) {
				std::cerr << "Error during async receive: " << error.value() << "\n";
				return;
			}

			try {
				std::string data(receive_buffer_.data(), bytes_received);
				Enemies entity_list;

				if (entity_list.ParseFromString(data)) {
					update_data(entity_list);
				}
				else {
					std::cerr << "Failed to parse Protobuf data!\n";
				}
			}
			catch (const std::exception& e) {
				std::cerr << "Exception during async processing: " << e.what() << "\n";
			}

			receive_data_async();
		});
}

void NetworkManager::update_data(Enemies& entity_list)
{
	for (auto player = entity_list.mutable_entries()->begin(); player != entity_list.mutable_entries()->end(); )
	{
		if (player->name() == g::local_player.name)
		{
			g::local_player.position = { player->x(), player->y(), player->z() };
			g::local_player.yaw = player->yaw();
			g::local_player.pitch = player->pitch();
			g::local_player.team = player->team();
			player = entity_list.mutable_entries()->erase(player);
		} else if (player->hp() <= 0 || player->team() == g::local_player.team)
		{
			player = entity_list.mutable_entries()->erase(player);
		}
		else 
		{
			++player;
		}
	}
#ifdef DEBUG
	g::packet_counter.fetch_add(1);
#endif
	g::entity_list = entity_list;
}
