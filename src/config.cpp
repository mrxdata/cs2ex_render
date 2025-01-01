#include "../include/config.h"

bool Config::espEnabled = true;
bool Config::showHealth = true;
bool Config::showWeapon = true;
bool Config::showArmor = true;
bool Config::showPlayerNames = true;
bool Config::showBoundingBoxes = true;
int Config::espColor[3] = { 255, 0, 0 };
int Config::viewmodel_fov = 68;

void Config::LoadConfig(const std::string& configFile) {
    std::ifstream file(configFile);
    if (!file.is_open()) return;

    Json::Value config;
    file >> config;

    espEnabled = config["espEnabled"].asBool();
    showHealth = config["showHealth"].asBool();
    showWeapon = config["showWeapon"].asBool();
    showArmor = config["showArmor"].asBool();
    showPlayerNames = config["showPlayerNames"].asBool();
    showBoundingBoxes = config["showBoundingBoxes"].asBool();
    espColor[0] = config["espColor"]["r"].asInt();
    espColor[1] = config["espColor"]["g"].asInt();
    espColor[2] = config["espColor"]["b"].asInt();
	viewmodel_fov = config["viewmodel_fov"].asInt();
}

void Config::SaveConfig(const std::string& configFile) {
    Json::Value config;
    config["espEnabled"] = espEnabled;
    config["showHealth"] = showHealth;
    config["showWeapon"] = showWeapon;
    config["showArmor"] = showArmor;
    config["showPlayerNames"] = showPlayerNames;
    config["showBoundingBoxes"] = showBoundingBoxes;
    config["viewmodel_fov"] = viewmodel_fov;

    Json::Value espColorConfig;
    espColorConfig["r"] = espColor[0];
    espColorConfig["g"] = espColor[1];
    espColorConfig["b"] = espColor[2];
    config["espColor"] = espColorConfig;
    std::ofstream file(configFile);
    file << config;
}
