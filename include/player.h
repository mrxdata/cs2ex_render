#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <DirectXMath.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include "../generated/enemies.pb.h"

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
    Player() :
        playerId(0),
        health(0),
        armor(0),
        isDefusing(false),
        position({0, 0, 0})
    { }

    static void updatePlayerPositions(const Enemies& enemies);
    static void updatePlayerList(const Enemies& enemies);
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
	static constexpr std::string playerName = "наст";
    float yaw;
    float pitch;
    XMFLOAT3 position;
    XMMATRIX projectionMatrix;
    XMMATRIX viewMatrix;

    LocalPlayer(int id, float yaw, float pitch, const XMFLOAT3& position)
        : playerId(id), yaw(yaw), pitch(pitch), position(position), projectionMatrix(XMMatrixIdentity()), viewMatrix(XMMatrixIdentity()) {
    }

    LocalPlayer() : playerId(0), yaw(0), pitch(0), position({0, 0, 0}), projectionMatrix(XMMatrixIdentity()), viewMatrix(XMMatrixIdentity()) {
        //update();
    }

    //void update();
    void updateMatrices();

};

#endif // PLAYER_H
