#include <Windows.h>
#include <iostream>
#include "../include/globals.h"
#include "../include/render.h"

LRESULT __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_CREATE:
    {
		g::hdcBuffer = CreateCompatibleDC(NULL);
		g::hbmBuffer = CreateCompatibleBitmap(GetDC(hWnd), g::SCREEN_WIDTH, g::SCREEN_HEIGHT);
		SelectObject(g::hdcBuffer, g::hbmBuffer);

        SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

        SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 0, LWA_COLORKEY);
        std::cout << "[+] Overlay created successfully" << std::endl;
        break;
    }
    case WM_ERASEBKGND:
        return TRUE;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        FillRect(g::hdcBuffer, &ps.rcPaint, (HBRUSH)GetStockObject(WHITE_BRUSH));

        //if (GetForegroundWindow() == g_game.process->hwnd_) {
        //    //render::RenderText(g::hdcBuffer, 10, 10, "cs2 | ESP", RGB(75, 175, 175), 15);
        //    hack::loop();
        //}
		Render::DrawBorderedBox(g::hdcBuffer, g::SCREEN_WIDTH / 2, g::SCREEN_HEIGHT / 2, 90, 160, RGB(255, 0, 0));

        BitBlt(hdc, 0, 0, g::SCREEN_WIDTH, g::SCREEN_HEIGHT, g::hdcBuffer, 0, 0, SRCCOPY);

        EndPaint(hWnd, &ps);
        InvalidateRect(hWnd, NULL, TRUE);
		break;
    }
    case WM_DESTROY:
    {
        DeleteDC(g::hdcBuffer);
        DeleteObject(g::hbmBuffer);
        PostQuitMessage(0);
        break;
    }
    default:
        //std::cout << "Default\n";
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}

int main() {
    SetConsoleTitle("EXTOVRL");

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);    
    wc.lpfnWndProc = WndProc;

	//wc.style = CS_HREDRAW 
 //            | CS_VREDRAW 
 //            | WS_EX_TRANSPARENT 
 //            | WS_EX_TOPMOST 
 //            | WS_EX_LAYERED 
 //            | WS_EX_TOOLWINDOW 
 //            | WS_EX_NOACTIVATE 
 //            | WS_EX_COMPOSITED;

    wc.style = CS_HREDRAW | CS_VREDRAW;

    wc.hbrBackground = WHITE_BRUSH;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "OVRL";
    wc.lpszMenuName = "MENU";
    RegisterClassExA(&wc);

    HWND hWnd = CreateWindowExA(
        WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
        wc.lpszClassName,
        "OVR",
        WS_POPUP,
        CW_USEDEFAULT, // left(x)
		CW_USEDEFAULT, // top(y)
		g::SCREEN_WIDTH, // width
		g::SCREEN_HEIGHT, // height
        NULL,
        NULL,
        wc.hInstance,
        NULL
    );

    if (hWnd == NULL) {
        std::cerr << "Window creation failed!" << std::endl;
        return 1;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}