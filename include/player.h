#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <DirectXMath.h>

using namespace DirectX;
using DirectX::XMFLOAT3;

class Player {
public:
    int playerId;
    int health;
    int armor;
    XMFLOAT3 position;
    bool isDefusing;

	Player(int id, bool isDefusing,
           int health, int armor, 
           const XMFLOAT3& position)
     : 
           playerId(id),  
           health(health), armor(armor), 
           isDefusing(isDefusing), 
           position(position)
           { }
    Player() {
        update();
    }
    void update();
    static void updatePlayerList();
};

class LocalPlayer {
public:
    static LocalPlayer& getInstance() {
		static LocalPlayer instance;
        return instance;
    }

    LocalPlayer(const LocalPlayer&) = delete;
    LocalPlayer& operator=(const LocalPlayer&) = delete;

    int playerId;
    float yaw;
    float pitch;
    DirectX::XMFLOAT3 position;
    XMMATRIX projectionMatrix;
    XMMATRIX viewMatrix;

    LocalPlayer(int id, float yaw, float pitch, const DirectX::XMFLOAT3& position)
        : playerId(id), yaw(yaw), pitch(pitch), position(position) {
    }

    LocalPlayer() {
        update();
    }

    void update();
    void updateMatrices(); // Объявление метода updateMatrices

};

#endif // PLAYER_H
