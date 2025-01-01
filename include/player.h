#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct Vector3 {
    float x, y, z;
};

class Player {
public:
    int playerId;
    int team;
    int health;
    int armor;
    Vector3 origin;

    struct Bones {
        Vector3 head, spine_1, spine_2, pelvis;
        Vector3 arm_upper_L, arm_lower_L, hand_L;
        Vector3 arm_upper_R, arm_lower_R, hand_R;
        Vector3 leg_upper_L, leg_lower_L, ankle_L;
        Vector3 leg_upper_R, leg_lower_R, ankle_R;
    } bones;

    std::string weapon;
    bool isDefusing;
    bool isSpotted;
    int money;
    float flashAlpha;

    Player(int id, int team, int health, int armor, const std::string& weapon,
        bool isDefusing, bool isSpotted, int money, float flashAlpha,
        const Vector3& origin)
        : playerId(id), team(team), health(health), armor(armor), weapon(weapon),
        isDefusing(isDefusing), isSpotted(isSpotted), money(money), flashAlpha(flashAlpha), origin(origin) {
    }

    void update();
};

#endif // PLAYER_H
