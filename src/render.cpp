#include "../include/render.h"
#include "../include/vector.h"
#include "../include/graphics.h"
#include "../include/globals.h"
#include "../include/time_counter.h"
#undef min
#undef max

void Render::RenderESP(LocalPlayer& local_player, const Enemies& entity_list)
{
    for (const auto& player : entity_list.entries())
    {
        Vector3 player_pos = { player.x(), player.y(), player.z() };

        if (player.name() == local_player.name) 
        {
            local_player.position = player_pos;
            local_player.yaw = player.yaw();
            local_player.pitch = player.pitch();
           /* std::cout << "LocalPlayer:\n x: "
                << local_player.position.x
                << " y: " << local_player.position.y
                << " z: " << local_player.position.z
                << " yaw: " << local_player.yaw
                << " pitch: " << local_player.pitch << "\n";*/
            continue;
        }

        if (local_player.position == player_pos)
        {
            continue;
        }
        /*std::cout << "Player:\n x: "
            << player.x()
            << " y: " << player.y()
            << " z: " << player.z() << "\n";

        std::cout << "pre box\n";*/

        Matrix4 view_matrix = graphics::createViewMatrix(local_player);
        Matrix4 projection_matrix = graphics::createProjectionMatrix();

        Vector3 screen_pos = graphics::world_to_screen(player_pos, view_matrix, projection_matrix);

        float base_width = 180.0f;
        float base_height = 340.0f;

        float scale_factor = 1.0f; // std::max(0.1f, 1.0f / (screen_pos.z * 2.f)); // do this

        float box_width = base_width * scale_factor;
        float box_height = base_height * scale_factor;

        //printf("X: %f, Y: %f width: %f height: %f\n", screen_pos.x, screen_pos.y, box_width, box_height);

        DrawBorderedBox(
            g::hdcBuffer,
            g::SCREEN_WIDTH - screen_pos.x - box_width / 2,  
            g::SCREEN_HEIGHT - screen_pos.y - box_height / 2,
            box_width,
            box_height,
            RGB(255, 0, 0)
        );
        g::timer.stop();
        g::timer.print_duration();
        /*DrawBorderedBox(
            g::hdcBuffer,
            1448,
            g::SCREEN_HEIGHT - 571,
            180,
            340,
            RGB(255, 0, 0)
        );*/
        //g::timer.stop();
        //g::timer.print_duration();
        //DrawBorderedBox(g::hdcBuffer, screen_pos.x, screen_pos.y, box_size, box_size * 1.8f, RGB(255, 0, 0));
    }
}

void Render::DrawCircle(HDC hdc, int x, int y, int radius, COLORREF color)
{
    HPEN hPen = CreatePen(PS_SOLID, 2, color);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Arc(hdc, x - radius, y - radius, x + radius, y + radius, 0, 0, 0, 0);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
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

