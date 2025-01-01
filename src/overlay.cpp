#include "../include/render.h"
#include "../include/overlay.h"
#include "../include/config.h"

LRESULT HandleWM_PAINT(HWND hwnd);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT:
        return HandleWM_PAINT(hwnd);
    case WM_TIMER:
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

LRESULT HandleWM_PAINT(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    EndPaint(hwnd, &ps);
    return 0;
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
    RegisterWindowClass(CLASS_NAME);

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

void Overlay::RegisterWindowClass(const wchar_t* className) {
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wc.lpszClassName = className;

    RegisterClassEx(&wc);
}

void Overlay::RunMessageLoop() {
    HWND cs2Window = NULL;
    bool cs2Active = false;

    SetTimer(hwnd_, 1, 1000 / 60, NULL);

    MSG msg = {};
    std::cout << "Waiting for CS2 window..." << std::endl;

    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_TIMER) {
            ProcessEspKey();
            HandleCS2Window(cs2Window, cs2Active);
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Overlay::ProcessEspKey() {
    static bool prevEspKeyState = false;
    bool currentEspKeyState = GetAsyncKeyState(Config::espKey) & 0x8000;

    if (currentEspKeyState && !prevEspKeyState) {
        Config::espEnabled = !Config::espEnabled;
        std::cout << "ESP toggled: " << (Config::espEnabled ? "Enabled" : "Disabled") << std::endl;
    }
    prevEspKeyState = currentEspKeyState;
}



void Overlay::HandleCS2Window(HWND& cs2Window, bool& cs2Active) {
    if (cs2Window == NULL) {
        cs2Window = FindCS2Window();
        if (cs2Window != NULL) {
            std::cout << "CS2 window found." << std::endl;
        }
    } else {
        bool isActive = IsCS2Active(cs2Window);
        HandleCS2Activity(cs2Active, isActive);
        cs2Active = isActive;
        UpdateOverlay(hwnd_, cs2Window);
    }
}

void Overlay::HandleCS2Activity(bool& cs2Active, bool isActive) {
    if (isActive != cs2Active) {
        std::cout << "CS2 window is " << (isActive ? "now active." : "no longer active.") << std::endl;
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
    if (IsCS2Active(cs2Window)) {
        if (Config::espEnabled) {
            Render(hwnd);
        }
        else {
            ClearOverlay(hwnd);
        }
    }
    else {
        ClearOverlay(hwnd);
    }
}