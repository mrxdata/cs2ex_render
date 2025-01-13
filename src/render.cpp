#include "../include/render.h"
#include "../include/vector.h"
#include "../include/graphics.h"
#include "../include/globals.h"
#include "../include/time_counter.h"
#undef min
#undef max

void Render::RenderESP()
{
    for (const auto& player : g::entity_list.entries())
    {
        Vector3 player_pos = { player.x(), player.y(), player.z() };

        if (g::local_player.position == player_pos)
        {
            continue;
        }

        Matrix4 view_matrix = graphics::createViewMatrix(g::local_player); 
        Matrix4 projection_matrix = graphics::createProjectionMatrix(); 

        Vector3 screen_pos = graphics::world_to_screen(player_pos, view_matrix, projection_matrix); 

        float base_width = 180.0f;
        float base_height = 340.0f;

        float scale_factor = 0.1f; //std::max(0.05f, 1.0f / (screen_pos.z * 2.f)); // do this

        float box_width = base_width * scale_factor;
        float box_height = base_height * scale_factor;

        //printf("X: %f, Y: %f width: %f height: %f\n", screen_pos.x, screen_pos.y, box_width, box_height);
        DrawCircle(
            g::hdcBuffer,
            g::SCREEN_WIDTH - screen_pos.x,
            screen_pos.y,
            //g::SCREEN_HEIGHT - screen_pos.y - box_height / 2.f,
            1,
            RGB(255, 0, 0)
        );
        //DrawBorderedBox(
        //    g::hdcBuffer,
        //    g::SCREEN_WIDTH - screen_pos.x,  
        //    screen_pos.y,
        //    //g::SCREEN_HEIGHT - screen_pos.y - box_height / 2.f,
        //    box_width,
        //    box_height,
        //    RGB(255, 0, 0)
        //);
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


