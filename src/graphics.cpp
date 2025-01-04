#include "../include/graphics.h"
#include "../include/globals.h"
#include "../include/local_player.h"
#include <array>

typedef std::array<std::array<float, 4>, 4> ViewMatrix;

namespace graphics {
    std::array<std::array<float, 4>, 4> create_view_matrix(const Vector3& view_pos, float yaw, float pitch, const Vector3& target_pos) {
        float cosYaw = std::cos(yaw);
        float sinYaw = std::sin(yaw);
        float cosPitch = std::cos(pitch);
        float sinPitch = std::sin(pitch);

        Vector3 forward = Vector3(cosPitch * sinYaw, sinPitch, cosPitch * cosYaw);
        Vector3 right = Vector3(sinYaw, 0, -cosYaw);
        Vector3 up = Vector3(-sinPitch * sinYaw, cosPitch, -sinPitch * cosYaw);

        Vector3 cameraToTarget = (target_pos - view_pos).normalize();

        return { {
            {right.x, up.x, -forward.x, 0},
            {right.y, up.y, -forward.y, 0},
            {right.z, up.z, -forward.z, 0},
            {-right.dot(view_pos), -up.dot(view_pos), forward.dot(view_pos), 1}
        } 
        };
    }

	Vector3 world_to_screen(Vector3* v, ViewMatrix view_matrix) {
		float w = view_matrix[3][0] * v->x + view_matrix[3][1] * v->y + view_matrix[3][2] * v->z + view_matrix[3][3];

		if (w < 0.01f) return { 0, 0, 0 };

		float _x = view_matrix[0][0] * v->x + view_matrix[0][1] * v->y + view_matrix[0][2] * v->z + view_matrix[0][3];
		float _y = view_matrix[1][0] * v->x + view_matrix[1][1] * v->y + view_matrix[1][2] * v->z + view_matrix[1][3];


		float inv_w = 1.0f / w;
		_x *= inv_w;
		_y *= inv_w;

		float x = g::SCREEN_WIDTH * 0.5f;
		float y = g::SCREEN_HEIGHT * 0.5f;

		x += 0.5f * _x * g::SCREEN_WIDTH + 0.5f;
		y -= 0.5f * _y * g::SCREEN_HEIGHT + 0.5f;

		return { x, y, w };
	}
}