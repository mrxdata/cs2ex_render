#ifndef OVERLAY_H
#define OVERLAY_H

#include <windows.h>
#include <iostream>


class HDCWrapper {
public:
    HDCWrapper(HDC hdc);
    ~HDCWrapper();
    HDC get() const;
private:
    HDC hdc_;
};

class HBITMAPWrapper {
public:
    HBITMAPWrapper(HBITMAP hbm);
    ~HBITMAPWrapper();
    HBITMAP get() const;
private:
    HBITMAP hbm_;
};

class Overlay {
public:
    static Overlay& GetInstance() {
        static Overlay instance;
        return instance;
    }

    void CreateOverlayWindow();
    void RunMessageLoop();
    HWND FindCS2Window();
    bool IsCS2Active(HWND cs2Window);
    void ClearOverlay(HWND hwnd);
    void UpdateOverlay(HWND hwnd, HWND cs2Window);

private:
    Overlay() : hwnd_(NULL) {}
    Overlay(const Overlay&) = delete;
    Overlay& operator=(const Overlay&) = delete;

    HWND hwnd_;
};

#endif // OVERLAY_H
