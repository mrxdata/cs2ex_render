#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
#include <sstream>
#include <json/json.h>

class Config {
public:
    static bool espEnabled;
    static bool showHealth;
    static bool showWeapon;
    static bool showArmor;
    static bool showPlayerNames;
    static bool showBoundingBoxes;
    static int espColor[3];
    static int viewmodel_fov;

    static void LoadConfig(const std::string& configFile);
    static void SaveConfig(const std::string& configFile);
};

#endif // CONFIG_H
