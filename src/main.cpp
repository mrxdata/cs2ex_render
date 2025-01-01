#include "../include/overlay.h"
#include "../include/render.h"

int main() {
    Overlay& overlay = Overlay::getInstance();
    overlay.CreateOverlayWindow();
    overlay.RunMessageLoop();
    return 0;
}
