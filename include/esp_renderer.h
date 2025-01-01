#pragma once
#ifndef ESP_RENDERER_H
#define ESP_RENDERER_H

#include "player.h"
#include "config.h"
#include <string>
#include <d3d11.h>

class ESPRenderer {
public:
    static inline ID3D11DeviceContext* pContext;
    static inline std::vector<Player> players = {};
    ESPRenderer(ID3D11DeviceContext* context) {
        pContext = context;
    }
    static void RenderESP();
};

#endif // ESP_RENDERER_H
