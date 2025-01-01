#include "../include/player.h"
#include "../include/esp_renderer.h"

using json = nlohmann::json;

void Player::updatePlayerList(const std::string& jsonData) {
    json playersJson = json::parse(jsonData);

    ESPRenderer::players.clear();

    for (size_t i = 0; i < playersJson.size(); ++i) {
        const auto& playerData = playersJson[i];
        std::string playerName = playerData["name"];

        if (playerName == LocalPlayer::playerName) {
            LocalPlayer& localPlayer = LocalPlayer::getInstance();
			localPlayer.playerId = static_cast<int>(i);
            localPlayer.position = { playerData["x"], playerData["y"], playerData["z"] };
            localPlayer.yaw = playerData["yaw"];
            localPlayer.pitch = playerData["yaw_z"];
            localPlayer.updateMatrices();
        }
        else {
            int id = static_cast<int>(i);

            ESPRenderer::players.push_back(Player(
                id,
                false,
                playerData["hp"],
                0,
                {
                    playerData["x"],
                    playerData["y"],
                    playerData["z"]
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

void Player::updatePlayerPositions(const std::string& jsonData) {
    json playersJson = json::parse(jsonData);
    LocalPlayer& localPlayer = LocalPlayer::getInstance();

    for (size_t i = 0; i < playersJson.size(); ++i) {
        const auto& playerData = playersJson[i];
        int id = static_cast<int>(i);

        auto it = std::find_if(ESPRenderer::players.begin(), ESPRenderer::players.end(),
            [id](const Player& player) { return player.playerId == id; });

        if (it != ESPRenderer::players.end()) {
            it->position = { 
                playerData["x"], 
                playerData["y"], 
                playerData["z"]
            };
        }
        if (id == localPlayer.playerId) {
            localPlayer.position = { playerData["x"], playerData["y"], playerData["z"] };
            localPlayer.yaw = playerData["yaw"];
            localPlayer.pitch = playerData["yaw_z"];
        }
    }
}

//void Player::updatePlayer(XMFLOAT3 position)
//{
//	this->position = position;
//}
//
//void LocalPlayer::update()
//{
//	//position = { 1110, 0, -583 };
//	//yaw = 34;
//	//pitch = 0;
//	//Player::updatePlayerList();
//	//updateMatrices();
//}

void LocalPlayer::updateMatrices() {
	projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(54), 1920.0f / 1080.0f, 0.01f, 1000.0f);
	viewMatrix = ESPRenderer::CreateViewMatrixFromYawPitch(position, yaw, pitch);
}