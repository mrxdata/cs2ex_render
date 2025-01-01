#include "../include/overlay.h"
#include "../include/render.h"

int main() {
    Overlay& overlay = Overlay::GetInstance();
    overlay.CreateOverlayWindow();
    overlay.RunMessageLoop();
    return 0;
}
