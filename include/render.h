#pragma once
#include <wtypes.h>

namespace render {

	void DrawCircle(HDC hdc, int x, int y, int radius, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 2, color);
		HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

		Arc(hdc, x - radius, y - radius, x + radius, y + radius, 0, 0, 0, 0);

		SelectObject(hdc, hOldPen);
		DeleteObject(hPen);
	}

    void DrawBorderedBox(HDC hdc, int x, int y, int width, int height, int thickness, COLORREF borderColor)
    {
        HPEN hPen = CreatePen(PS_SOLID, thickness, borderColor);
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen); 

        Rectangle(hdc, x, y, x + width, y + height);

        SelectObject(hdc, hOldPen);

        DeleteObject(hPen);
    }


}
