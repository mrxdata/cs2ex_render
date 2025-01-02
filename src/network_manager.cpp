#include "../include/network_manager.h"
#include "../include/player.h"
#include "../include/esp_renderer.h"

using boost::asio::ip::udp;

    NetworkManager::NetworkManager(boost::asio::io_context& io_context, const std::string& server_ip, unsigned short server_port)
        : socket_(io_context, udp::endpoint(udp::v4(), 7000)),
        server_endpoint_(boost::asio::ip::address::from_string(server_ip), server_port) {
        startReceiving();
    }

    void NetworkManager::startReceiving() {
        receiveData();
    }

    void NetworkManager::receiveData() {
        socket_.async_receive_from(
            boost::asio::buffer(receive_buffer_), server_endpoint_,
            [this](boost::system::error_code ec, std::size_t bytes_received) {
                if (!ec) {
                    processData(bytes_received);
                }
                else {
                    std::cerr << "Error while receiving data: " << ec.message() << std::endl;
                }
                receiveData();
            });
    }

    void NetworkManager::processData(std::size_t bytes_received) {
        std::string data(receive_buffer_.data(), bytes_received);

        Enemies enemies;
        if (enemies.ParseFromString(data)) {
            bool playersChanged = hasPlayersListChanged(enemies);

            if (playersChanged) {
                Player::updatePlayerList(enemies);
            }

            Player::updatePlayerPositions(enemies);
        }
        else {
            std::cerr << "Failed to parse Protobuf data!" << std::endl;
        }
    }

    bool NetworkManager::hasPlayersListChanged(const Enemies& newEnemies) {
        if (newEnemies.entries_size() != ESPRenderer::players.size()) {
            return true;
        }

        for (size_t i = 0; i < newEnemies.entries_size(); ++i) {
            const auto& newEnemy = newEnemies.entries(i);
            bool found = false;

            for (const auto& existingPlayer : ESPRenderer::players) {
                if (existingPlayer.playerId == static_cast<int>(i) &&
                    existingPlayer.position.x == newEnemy.x() &&
                    existingPlayer.position.y == newEnemy.y() &&
                    existingPlayer.position.z == newEnemy.z()) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return true;
            }
        }

        return false; 
    }

