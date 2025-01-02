#include "../include/player.h"
#include "../include/esp_renderer.h"

void Player::updatePlayerList(const Enemies& enemies) {
    ESPRenderer::players.clear();

    for (size_t i = 0; i < enemies.entries_size(); ++i) {
        const auto& enemy = enemies.entries(i);
        std::string playerName = enemy.name();

        if (playerName == LocalPlayer::playerName) {
            LocalPlayer& localPlayer = LocalPlayer::getInstance();
            localPlayer.playerId = static_cast<int>(i);
            localPlayer.position = { enemy.x(), enemy.y(), enemy.z() };
            localPlayer.yaw = enemy.yaw();
            localPlayer.pitch = enemy.pitch();
            localPlayer.updateMatrices();
        }
        else {
            int id = static_cast<int>(i);

            ESPRenderer::players.emplace_back(Player(
                id,
                false,
                enemy.hp(),
                0,
                {
                    enemy.x(),
                    enemy.y(),
                    enemy.z(),
                }
            ));
        }
    }

    for (const auto& player : ESPRenderer::players) {
        std::cout << "Player ID: " << player.playerId << "  "
            << "x: " << player.position.x << "  "
            << "y: " << player.position.y << "  "
            << "z: " << player.position.z << "  "
            << "\n";
    }
}

void Player::updatePlayerPositions(const Enemies& enemies) {
    LocalPlayer& localPlayer = LocalPlayer::getInstance();

    for (const auto& enemy : enemies.entries()) {
        int id = static_cast<int>(&enemy - &enemies.entries(0));

        auto it = std::find_if(ESPRenderer::players.begin(), ESPRenderer::players.end(),
            [id](const Player& player) { return player.playerId == id; });

        if (it != ESPRenderer::players.end()) {
            it->position = { enemy.x(), enemy.y(), enemy.z() };
        }

        if (id == localPlayer.playerId) {
            localPlayer.position = { enemy.x(), enemy.y(), enemy.z() };
            localPlayer.yaw = enemy.yaw();
            localPlayer.pitch = enemy.pitch();
        }
    }
}

void LocalPlayer::updateMatrices() {
	projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(54), 1920.0f / 1080.0f, 0.01f, 1000.0f);
	viewMatrix = ESPRenderer::CreateViewMatrixFromYawPitch(position, yaw, pitch);
}