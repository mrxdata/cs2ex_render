#include "../include/network_manager.h"
#include "../include/globals.h"
#include "../include/render.h"
#include "../include/time_counter.h"
#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>

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
        std::cout << "[+] Overlay created successfully\n";
        break;
    }
    case WM_ERASEBKGND:
        return TRUE;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        FillRect(g::hdcBuffer, &ps.rcPaint, (HBRUSH)GetStockObject(WHITE_BRUSH));

        Render::RenderESP();

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
    
    std::string server_ip = "46.191.235.182"; 
    std::string server_port = "7000"; 

    NetworkManager network_manager(server_ip, server_port); 
   
    network_manager.start(); 
	network_manager.send_udp_hello();  
    network_manager.receive_data_async();  
    network_manager.run_io_service();

#ifdef DEBUG
    std::thread counter_thread([]() {
        g::timer.start();
        while (true)
        {
            if (g::msg_counter.load() % 100 == 0)
            {
                printf("MSG: %d | PACKET: %d | RENDER: %d | TIME: %s\n", g::msg_counter.load(), g::packet_counter.load(), g::render_counter.load(), g::timer.return_duration("ms"));
            }
            std::this_thread::sleep_for(std::chrono_milliseconds(1000));
        }
        });
    counter_thread.detach();
#endif

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
#ifdef DEBUG
        g::msg_counter.fetch_add(1);
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }


#ifdef DEBUG
    counter_thread.join();
#endif
    return 0;
}