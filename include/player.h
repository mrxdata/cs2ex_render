#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <DirectXMath.h>

using namespace DirectX;

struct Vector3 {
    float x, y, z;
};

class Player {
public:
    int playerId;
    int health;
    int armor;
    Vector3 position;
    bool isDefusing;

	Player(int id, bool isDefusing,
           int health, int armor, 
           float yaw, float pitch, 
           const Vector3& position)
     : 
           playerId(id),  
           health(health), armor(armor), 
           isDefusing(isDefusing), 
           position(position)
           { }

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
    Vector3 position;
    XMMATRIX projectionMatrix;
    XMMATRIX viewMatrix;

    LocalPlayer(int id, bool IsLocalPlayer, int health, int armor, float yaw, float pitch, const Vector3& position)
        : playerId(id), yaw(yaw), pitch(pitch), position(position), projectionMatrix(XMMatrixIdentity()), viewMatrix(XMMatrixIdentity()) {
    }

    LocalPlayer() {}

    void update();
    struct Vector3 {
        XMFLOAT3 x, y, z;
    };
    void updateMatrices(); // Объявление метода updateMatrices

};

#endif // PLAYER_H
