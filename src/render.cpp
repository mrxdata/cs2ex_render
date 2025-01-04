#include "../include/render.h"
#include "../include/vector.h"
#include "../include/graphics.h"
#include "../include/globals.h"

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

void Render::RenderESP(LocalPlayer& local_player, const Enemies& entity_list)
{
    for (int i = 0; i < entity_list.entries_size(); i++)
    {
        const auto& player = entity_list.entries(i);

        Vector3 player_pos = Vector3(player.x(), player.y(), player.z());

        if (player.name() == local_player.name) 
        {
            local_player.id = i; 
            continue;
        }

        local_player.view_matrix = graphics::create_view_matrix(local_player.position, player.yaw(), player.pitch(), player_pos);

        float distance = local_player.position.calculate_distance(player_pos);

        float box_size = 160.0f / (1.0f + distance * 0.1f);

        Vector3 screen_pos = graphics::world_to_screen(&player_pos, local_player.view_matrix);

        //if (screen_pos.z < 0.01f) continue;

        DrawBorderedBox(g::hdcBuffer, screen_pos.x, screen_pos.y, box_size, box_size * 1.8f, RGB(255, 0, 0));
    }
}


