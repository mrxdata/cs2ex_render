#pragma once
#ifndef ESP_RENDERER_H
#define ESP_RENDERER_H

#include "player.h"
#include "config.h"
#include <string>
#include <d3d11.h>

class ESPRenderer {
public:
    static inline ID3D11DeviceContext* pContext = nullptr;
    static inline ID3D11Device* pDevice = nullptr;
    static inline std::vector<Player> players = {};
    ESPRenderer(ID3D11DeviceContext* context) {
        pContext = context;
    }
    static void RenderESP(void* pvBits);
    static DirectX::XMMATRIX CreateViewMatrixFromYawPitch(const DirectX::XMFLOAT3& cameraPosition, float yaw, float pitch);
};

#endif // ESP_RENDERER_H
