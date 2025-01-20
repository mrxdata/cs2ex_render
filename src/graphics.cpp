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
    float fov_horizontal = 135.f;
    float min_distance = 32.0f;
    float max_distance = 2000.0f;

    glm::mat4 createViewMatrix(const LocalPlayer& local_player) {
        float camera_height = 0.f;

        glm::vec3 camera_pos(local_player.position.x, local_player.position.y + camera_height, local_player.position.z);
        float yaw_rads = glm::radians(local_player.yaw);

        if (yaw_rads > glm::pi<float>()) {
            yaw_rads -= glm::two_pi<float>();
        }

        float pitch_rads = glm::radians(local_player.pitch);

        glm::vec3 forward(
            std::cos(pitch_rads) * std::cos(yaw_rads),
            -std::sin(pitch_rads),
            std::cos(pitch_rads) * std::sin(yaw_rads) 
        );

        forward = glm::normalize(forward);

        glm::vec3 target = camera_pos + forward;

        glm::vec3 up(0.0f, 1.0f, 0.0f);

        return glm::lookAt(camera_pos, target, up);
    }

    glm::mat4 createProjectionMatrix() {
        float fov_vertical = glm::radians(graphics::fov_horizontal) / g::ASPECT_RATIO;
        return glm::perspective(fov_vertical, g::ASPECT_RATIO, graphics::min_distance, graphics::max_distance);
    }

    bool world_to_screen(const glm::vec3& position, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, glm::vec3& screen) {
        glm::vec4 clipSpace = projectionMatrix * viewMatrix * glm::vec4(position, 1.0f);

        if (clipSpace.w <= 0.01f) {
            return false;
        }

        glm::vec3 ndc = glm::vec3(clipSpace) / clipSpace.w;

        screen.x = g::SCREEN_WIDTH - ((ndc.x + 1.0f) * 0.5f * g::SCREEN_WIDTH);
        screen.y = (1.0f - ndc.y) * 0.5f * g::SCREEN_HEIGHT;
        screen.z = clipSpace.w;

        return true;
    }
  
}