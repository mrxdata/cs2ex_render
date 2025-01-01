#ifndef OVERLAY_H
#define OVERLAY_H

#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

class HDCWrapper {
public:
    explicit HDCWrapper(HDC hdc);
    ~HDCWrapper();
    HDC get() const;

private:
    HDC hdc_;
};

class HBITMAPWrapper {
public:
    explicit HBITMAPWrapper(HBITMAP hbm);
    ~HBITMAPWrapper();
    HBITMAP get() const;

private:
    HBITMAP hbm_;
};

class Overlay {
public:
    static Overlay& getInstance() {
        static Overlay instance;
        return instance;
    }
    Overlay() = default;
    void CreateOverlayWindow();
    void RunMessageLoop();
    void UpdateOverlay(HWND hwnd, HWND cs2Window);

private:
    void RegisterWindowClass(const wchar_t* className);
    void ProcessEspKey();
    void HandleCS2Window(HWND& cs2Window, bool& cs2Active);
    void HandleCS2Activity(bool& cs2Active, bool isActive);
    void ClearOverlay(HWND hwnd);
    HWND FindCS2Window();
    bool IsCS2Active(HWND cs2Window);

    HWND hwnd_ = nullptr;
};

#endif // OVERLAY_H
