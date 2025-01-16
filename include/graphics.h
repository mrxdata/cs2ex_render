#pragma once
#include "vector.h"
#include <array>
#include "local_player.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

struct Matrix4 {
    float data[4][4] = { 0 };

    Matrix4() {
        for (int i = 0; i < 4; ++i) {
            data[i][i] = 1.0f;
        }
    }

    Vector4 operator*(const Vector4& vec) const noexcept {
        return {
            {
            data[0][0] * vec.x + data[0][1] * vec.y + data[0][2] * vec.z + data[0][3] * vec.w,
            data[1][0] * vec.x + data[1][1] * vec.y + data[1][2] * vec.z + data[1][3] * vec.w,
            data[2][0] * vec.x + data[2][1] * vec.y + data[2][2] * vec.z + data[2][3] * vec.w
            },
            data[3][0] * vec.x + data[3][1] * vec.y + data[3][2] * vec.z + data[3][3] * vec.w
        };
    }

    Matrix4 operator*(const Matrix4& other) const noexcept {
        Matrix4 result;
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                result.data[row][col] = 0;
                for (int k = 0; k < 4; ++k) {
                    result.data[row][col] += data[row][k] * other.data[k][col];
                }
            }
        }
        return result;
    }

    void setLookAt(const Vector3& position, const Vector3& target, const Vector3& up) noexcept {
        Vector3 forward = (target - position).normalize();
        Vector3 right = up.cross(forward).normalize();
        Vector3 cameraUp = forward.cross(right);

        data[0][0] = right.x;    data[0][1] = right.y;    data[0][2] = right.z;    data[0][3] = -right.x * position.x - right.y * position.y - right.z * position.z;
        data[1][0] = cameraUp.x; data[1][1] = cameraUp.y; data[1][2] = cameraUp.z; data[1][3] = -cameraUp.x * position.x - cameraUp.y * position.y - cameraUp.z * position.z;
        data[2][0] = forward.x;  data[2][1] = forward.y;  data[2][2] = forward.z;  data[2][3] = -forward.x * position.x - forward.y * position.y - forward.z * position.z;
        data[3][0] = 0;          data[3][1] = 0;          data[3][2] = 0;          data[3][3] = 1;
    }
};

namespace graphics {
    glm::mat4 createViewMatrix(const LocalPlayer& local_player);
    glm::mat4 createProjectionMatrix();
    glm::vec3 world_to_screen(const glm::vec3& position, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
}