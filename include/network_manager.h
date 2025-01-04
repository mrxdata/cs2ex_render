#include <boost/asio.hpp>
#include <string>
#include "../generated/enemies.pb.h"

class NetworkManager {
public:
	NetworkManager(const std::string& host, const std::string& port);
	~NetworkManager();

	void stop();
	void send_udp_hello();
	Enemies receive_data();
	std::atomic<bool> is_running{ false };

private:
	void _start();
	std::unique_ptr<std::thread> io_thread;
	boost::asio::io_context io_context;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint server_endpoint;
	std::array<char, 4096> receive_buffer_;
	std::string host;
	std::string port;
};