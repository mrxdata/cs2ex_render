#include "../include/player.h"
#include "../include/esp_renderer.h"


void Player::updatePlayerList() {
	Player player1(1, false, 100, 100, { 1422, 0, -367 });
	Player player2(1, false, 100, 100, { 1522, 30, -387 });
	ESPRenderer::players.push_back(player1);
	ESPRenderer::players.push_back(player2);
}

void Player::update()
{

}


void LocalPlayer::update()
{
	position = { 1110, 0, -583 };
	yaw = 34;
	pitch = 0;
	Player::updatePlayerList();
	updateMatrices();
}

void LocalPlayer::updateMatrices() {
	projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(54), 1920.0f / 1080.0f, 0.01f, 1000.0f);
	viewMatrix = ESPRenderer::CreateViewMatrixFromYawPitch(position, yaw, pitch);
}