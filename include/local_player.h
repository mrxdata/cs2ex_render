#pragma once
#include <array>
#include <string>
#include "vector.h"

typedef std::array<std::array<float, 4>, 4> ViewMatrix;

struct LocalPlayer {
	LocalPlayer() : position({0, 0, 0}), yaw(0), pitch(0), id(-1), team("") {
		view_matrix = { {
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		} };
	}
	Vector3 position;
	float yaw, pitch;
	int id;
	std::string team;
	std::string name = "death'o'durunt";
	ViewMatrix view_matrix;
};