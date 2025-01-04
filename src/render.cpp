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

void Render::RenderESP(LocalPlayer local_player, Enemies enemies)
{
	for (int i = 0; i < enemies.entries_size(); i++)
	{
		const auto& player = enemies.entries(i);

		if (player.name() == local_player.name)
		{
			local_player.playerId = i;
			continue;
		}

		Vector3 player_pos = Vector3(player.x(), player.y(), player.z());
		Vector3 screen_pos = graphics::world_to_screen(&player_pos, local_player.view_matrix);
		//if (screen_pos.z < 0.01f) continue;
		DrawBorderedBox(g::hdcBuffer, screen_pos.x, screen_pos.y, 90, 160, RGB(255, 0, 0));
	}
}

