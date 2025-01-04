#pragma once
#include "vector.h"
#include <array>

typedef std::array<std::array<float, 4>, 4> ViewMatrix;

namespace graphics {
	std::array<std::array<float, 4>, 4> create_view_matrix(const Vector3& view_pos, float yaw, float pitch, const Vector3& target_pos);
	Vector3 world_to_screen(Vector3* v, ViewMatrix view_matrix);
}