#pragma once
#include <wtypes.h>
#include "local_player.h"
#include "../generated/enemies.pb.h"

namespace Render {

	void DrawCircle(HDC hdc, int x, int y, int radius, COLORREF color);
	void DrawBorderedBox(HDC hdc, int x, int y, int w, int h, COLORREF borderColor);
	void RenderESP(LocalPlayer& local_player, const Enemies& enemies);

}
