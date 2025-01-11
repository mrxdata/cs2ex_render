#include "../include/graphics.h"
#include "../include/globals.h"
#include "../include/local_player.h"
#include <numbers>
#include <array>
#include <cmath>
#include <algorithm>
#undef min
#undef max

namespace graphics {

    float fov_vertical = 82.0f;
    float fov_horizontal = 101.085f;
    float min_distance = 32.0f;
    float max_distance = 2000.0f;

	float inline to_radians(float degrees) {
		return degrees * std::numbers::pi_v<float> / 180.0f;
	}

    Matrix4 createViewMatrix(const LocalPlayer& local_player) {
        Matrix4 viewMatrix;

        float yaw_rads = to_radians(local_player.yaw);
        float pitch_rads = to_radians(local_player.pitch);

        Vector3 forward(
            std::cos(pitch_rads) * std::cos(yaw_rads),
            std::sin(pitch_rads),
            std::cos(pitch_rads) * std::sin(yaw_rads)
        );

        Vector3 up(0.0f, 1.0f, 0.0f);
        viewMatrix.setLookAt(local_player.position, local_player.position + forward, up);
        return viewMatrix;
    }

    Matrix4 createProjectionMatrix() {
        Matrix4 projection;
        float tan_half_fov = std::tan(to_radians(fov_vertical * 0.5f));

        projection.data[0][0] = 1.0f / (g::ASPECT_RATIO * tan_half_fov);
        projection.data[1][1] = 1.0f / tan_half_fov;
        projection.data[2][2] = -(max_distance + min_distance) / (max_distance - min_distance);
        projection.data[2][3] = -(2.0f * max_distance * min_distance) / (max_distance - min_distance);
        projection.data[3][2] = -1.0f;
        projection.data[3][3] = 0.0f;

        return projection;
    }

    Vector3 world_to_screen(const Vector3& position, const Matrix4& viewMatrix, const Matrix4& projectionMatrix) {
        Vector4 clipSpace = projectionMatrix * viewMatrix * Vector4(position, 1.0f);

        if (clipSpace.w == 0.0f) {
            return { -1.0f, -1.0f };
        }

        float ndcX = clipSpace.x / clipSpace.w;
        float ndcY = clipSpace.y / clipSpace.w;

        float screenX = (ndcX + 1.0f) * 0.5f * g::SCREEN_WIDTH;
        float screenY = (1.0f - ndcY) * 0.5f * g::SCREEN_HEIGHT;

        return { screenX, screenY, clipSpace.w };
    }
}