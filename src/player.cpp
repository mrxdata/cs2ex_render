#include "../include/player.h"
#include "../include/esp_renderer.h"

void Player::updatePlayerList() {
	Player player1(1, false, 100, 100, 0, 0, { 0, 0, 0 });
	ESPRenderer::players.push_back(player1);
	LocalPlayer local_player(2, true, 100, 100, 0, 0, { 0, 0, 0 });
}

void LocalPlayer::updateMatrices() {
	XMFLOAT3 positionFloat3(position.x, position.y, position.z);
	viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&positionFloat3), XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	projectionMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1920.0f / 1080.0f, 0.01f, 1000.0f);
}