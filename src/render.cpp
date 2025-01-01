#include "../include/render.h"
#include "../include/overlay.h"
#include "../include/esp_renderer.h"

namespace RenderResources {
    HDC hdcMem = NULL;
    HBITMAP hbmAlpha = NULL;
    HBITMAP hbmOld = NULL;
    void* pvBits = nullptr;
    SIZE screenSize = { 0, 0 };
    BLENDFUNCTION blend = { 0 };
    bool initialized = false;
    HDC hdcScreen = NULL;

    POINT ptSrc = { 0, 0 };
    POINT ptDst = { 0, 0 };

    void Initialize() {
        if (!initialized) {
            hdcScreen = GetDC(NULL);

            hdcMem = CreateCompatibleDC(hdcScreen);

            BITMAPINFO bmi = { 0 };
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = GetSystemMetrics(SM_CXSCREEN);
            bmi.bmiHeader.biHeight = -GetSystemMetrics(SM_CYSCREEN);
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 32;
            bmi.bmiHeader.biCompression = BI_RGB;

            screenSize = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };

            hbmAlpha = CreateDIBSection(hdcMem, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0);

            memset(pvBits, 0, screenSize.cx * screenSize.cy * 4);

            blend.BlendOp = AC_SRC_OVER;
            blend.BlendFlags = 0;
            blend.SourceConstantAlpha = 255;
            blend.AlphaFormat = AC_SRC_ALPHA;

            if (hbmAlpha == NULL) {
                return;
            }
            hbmOld = (HBITMAP)SelectObject(hdcMem, hbmAlpha);
            initialized = true;

        }
    }

    void Cleanup() {
        if (initialized) {
            SelectObject(hdcMem, hbmOld);
            DeleteObject(hbmAlpha);
            DeleteDC(hdcMem);
            ReleaseDC(NULL, hdcScreen);

            initialized = false;
        }
    }
}

void Render(HWND hwnd) {
    RenderResources::Initialize();

    ESPRenderer::RenderESP(RenderResources::pvBits);

    UpdateLayeredWindow(hwnd, RenderResources::hdcScreen, &RenderResources::ptDst,
        &RenderResources::screenSize, RenderResources::hdcMem,
        &RenderResources::ptSrc, RGB(0, 0, 0),
        &RenderResources::blend, ULW_ALPHA);
}

void CleanupRender() {
    RenderResources::Cleanup();
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

