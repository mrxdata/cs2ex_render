#include "../include/network_manager.h"
#include "../include/globals.h"
#include "../include/render.h"
#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "../include/time_counter.h"

std::string server_ip = "46.191.235.182"; 
std::string server_port = "7000"; 

NetworkManager network_manager(server_ip, server_port); 

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

        g::timer.start();
        g::entity_list = network_manager.receive_data();
        Render::RenderESP(g::local_player, g::entity_list);
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
    
   
	network_manager.send_udp_hello();

	//std::jthread data_thread([&]() {
	//	while (network_manager.is_running == true) {
 //           if (g::entity_list.entries_size() != 0)
 //           {
 //               //g::timer.start();
 //               //UpdateWindow(hWnd);
 //           }
 //           else
 //           {
 //               continue;
 //           }
	//		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	//	}
	//	});

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}