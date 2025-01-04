#pragma once
#include <array>
#include <string>

typedef std::array<std::array<float, 4>, 4> ViewMatrix;

struct LocalPlayer {
	LocalPlayer() : x(0), y(0), z(0), yaw(0), pitch(0) {
		view_matrix = { {
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		} };
	}
	float x, y, z;
	float yaw, pitch;
	int playerId;
	int team;
	std::string name = "nast";
	ViewMatrix view_matrix;
};