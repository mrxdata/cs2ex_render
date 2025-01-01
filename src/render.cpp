#include "../include/render.h"
#include "../include/overlay.h"
#include "../include/esp_renderer.h"

void Render(HWND hwnd) {
    HDC hdcScreen = GetDC(NULL);
    HDCWrapper hdcMem(CreateCompatibleDC(hdcScreen));
    HBITMAPWrapper hbmMem(CreateCompatibleBitmap(hdcScreen, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem.get(), hbmMem.get());

    BLENDFUNCTION blend = { 0 };
    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.SourceConstantAlpha = 255;
    blend.AlphaFormat = AC_SRC_ALPHA;

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = GetSystemMetrics(SM_CXSCREEN);
    bmi.bmiHeader.biHeight = -GetSystemMetrics(SM_CYSCREEN);
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* pvBits;
    HBITMAPWrapper hbmAlpha(CreateDIBSection(hdcMem.get(), &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0));
    HBITMAP hbmOldAlpha = (HBITMAP)SelectObject(hdcMem.get(), hbmAlpha.get());

    memset(pvBits, 0, GetSystemMetrics(SM_CXSCREEN) * GetSystemMetrics(SM_CYSCREEN) * 4);

    ESPRenderer::RenderESP();
    //DrawRedSquare(pvBits);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
    POINT ptDst = { 0, 0 };

    UpdateLayeredWindow(hwnd, hdcScreen, &ptDst, &sizeWnd, hdcMem.get(), &ptSrc, RGB(0, 0, 0), &blend, ULW_ALPHA);

    SelectObject(hdcMem.get(), hbmOldAlpha);
    ReleaseDC(NULL, hdcScreen);
}

void DrawRedSquare(void* pvBits)
{
    int width = 100;
    int height = 100;
    int x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
    int y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ((DWORD*)pvBits)[(y + i) * GetSystemMetrics(SM_CXSCREEN) + (x + j)] = 0xFFFF0000;
        }
    }
}

