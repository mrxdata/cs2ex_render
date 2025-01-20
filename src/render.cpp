#include "../include/render.h"
#include "../include/vector.h"
#include "../include/graphics.h"
#include "../include/globals.h"
#include "../include/time_counter.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#undef min
#undef max

constexpr float scale_factor = 25000.f; // Empirically found
glm::vec3 screen_pos;

void Render::RenderESP() {

    glm::mat4 view_matrix = graphics::createViewMatrix(g::local_player);
    glm::mat4 projection_matrix = graphics::createProjectionMatrix();

    for (const auto& player : g::entity_list.entries()) {
        glm::vec3 player_pos(player.x(), player.y(), player.z());

        if (g::local_player.position == player_pos) {
            continue;
        }

        if (!graphics::world_to_screen(player_pos, view_matrix, projection_matrix, screen_pos))
        {
            continue;
        }

        if (screen_pos.z > 0.0f) {
            float box_width = scale_factor / screen_pos.z;
            float box_height = box_width * 2.4f;
#ifdef DEBUG
            g::render_counter.fetch_add(1);
#endif
            Render::DrawBorderedBox(
                g::hdcBuffer,
                static_cast<int>(screen_pos.x - box_width / 2.f),
                static_cast<int>(screen_pos.y - box_height / 10.f),
                static_cast<int>(box_width),
                static_cast<int>(box_height),
                RGB(255, 0, 0)
            );
        }
    }
}

void Render::DrawBorderedBox(HDC hdc, int x, int y, int w, int h, COLORREF borderColor)
{
    HBRUSH hBorderBrush = CreateSolidBrush(borderColor);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBorderBrush);

    RECT rect = { x, y, x + w, y + h };
    FrameRect(hdc, &rect, hBorderBrush);

    SelectObject(hdc, hOldBrush);
    DeleteObject(hBorderBrush);
}

void Render::DrawCircle(HDC hdc, int x, int y, int radius, COLORREF color)
{
    HPEN hPen = CreatePen(PS_SOLID, 2, color);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Arc(hdc, x - radius, y - radius, x + radius, y + radius, 0, 0, 0, 0);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}


