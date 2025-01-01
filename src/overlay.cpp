#include "../include/render.h"
#include "../include/overlay.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_TIMER: {
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

HDCWrapper::HDCWrapper(HDC hdc) : hdc_(hdc) {}
HDCWrapper::~HDCWrapper() {
    if (hdc_) {
        DeleteDC(hdc_);
    }
}
HDC HDCWrapper::get() const { return hdc_; }

HBITMAPWrapper::HBITMAPWrapper(HBITMAP hbm) : hbm_(hbm) {}
HBITMAPWrapper::~HBITMAPWrapper() {
    if (hbm_) {
        DeleteObject(hbm_);
    }
}
HBITMAP HBITMAPWrapper::get() const { return hbm_; }

void Overlay::CreateOverlayWindow() {
    const wchar_t CLASS_NAME[] = L"OverlayWindowClass";

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wc.lpszClassName = CLASS_NAME;

    RegisterClassEx(&wc);

    hwnd_ = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT,
        CLASS_NAME,
        L"Overlay Window",
        WS_POPUP,
        0, 0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    if (hwnd_ == NULL) {
        std::cerr << "Failed to create window!" << std::endl;
        exit(1);
    }

    ShowWindow(hwnd_, SW_SHOW);
}

#include <thread>
#include <chrono>

void Overlay::RunMessageLoop() {
    HWND cs2Window = NULL;
    bool cs2Active = false;

    SetTimer(hwnd_, 1, 1000 / 60, NULL);

    MSG msg = {};
    std::cout << "Waiting for CS2 window..." << std::endl;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_TIMER) {
            if (cs2Window == NULL) {
                cs2Window = FindCS2Window();
                if (cs2Window != NULL) {
                    std::cout << "CS2 window found." << std::endl;
                }
            }
            else {
                bool isActive = IsCS2Active(cs2Window);
                if (isActive && !cs2Active) {
                    std::cout << "CS2 window is now active." << std::endl;
                }
                else if (!isActive && cs2Active) {
                    std::cout << "CS2 window is no longer active." << std::endl;
                }
                cs2Active = isActive;
                UpdateOverlay(hwnd_, cs2Window);
            }
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HWND Overlay::FindCS2Window() {
    HWND hwnd = NULL;
    EnumWindows([](HWND hWnd, LPARAM lParam) -> BOOL {
        char windowTitle[256];
        GetWindowTextA(hWnd, windowTitle, sizeof(windowTitle));
        if (std::string(windowTitle) == "Counter-Strike 2") {
            *reinterpret_cast<HWND*>(lParam) = hWnd;
            return FALSE;
        }
        return TRUE;
        }, reinterpret_cast<LPARAM>(&hwnd));
    return hwnd;
}

bool Overlay::IsCS2Active(HWND cs2Window) {
    return GetForegroundWindow() == cs2Window;
}

void Overlay::ClearOverlay(HWND hwnd) {
    HDC hdcScreen = GetDC(NULL);
    HDCWrapper hdcMem(CreateCompatibleDC(hdcScreen));
    HBITMAPWrapper hbmMem(CreateCompatibleBitmap(hdcScreen, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem.get(), hbmMem.get());

    BLENDFUNCTION blend = { 0 };
    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.SourceConstantAlpha = 0;
    blend.AlphaFormat = AC_SRC_ALPHA;

    RECT rect = { 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
    HBRUSH transparentBrush = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(hdcMem.get(), &rect, transparentBrush);
    DeleteObject(transparentBrush);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
    POINT ptDst = { 0, 0 };

    UpdateLayeredWindow(hwnd, hdcScreen, &ptDst, &sizeWnd, hdcMem.get(), &ptSrc, RGB(0, 0, 0), &blend, ULW_ALPHA);

    SelectObject(hdcMem.get(), hbmOld);
    ReleaseDC(NULL, hdcScreen);
}

void Overlay::UpdateOverlay(HWND hwnd, HWND cs2Window) {
    if (!IsCS2Active(cs2Window)) {
        ClearOverlay(hwnd);
        return;
    }

    Render(hwnd);
}
