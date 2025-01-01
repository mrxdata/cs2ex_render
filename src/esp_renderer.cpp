#include "../include/esp_renderer.h"
#include <DirectXMath.h>
#include <iostream>

using namespace DirectX;
using DirectX::XMFLOAT3;



//View Matrix
XMMATRIX ESPRenderer::CreateViewMatrixFromYawPitch(const XMFLOAT3& cameraPosition, float yaw, float pitch) {
    yaw = XMConvertToRadians(yaw);
    pitch = XMConvertToRadians(pitch);

    float cosPitch = cosf(pitch);
    XMVECTOR forward = XMVectorSet(
        cosPitch * cosf(yaw), // X component
        sinf(pitch),          // Y component
        cosPitch * sinf(yaw), // Z component
        0.0f                  // W component
    );

    forward = XMVector3Normalize(forward);

    XMVECTOR cameraPositionVec = XMLoadFloat3(&cameraPosition);
    XMVECTOR cameraTarget = XMVectorAdd(cameraPositionVec, forward);

    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    return XMMatrixLookAtLH(cameraPositionVec, cameraTarget, up);
}

bool WorldToScreen(const XMFLOAT3& worldPos, XMFLOAT3& screenPos, const LocalPlayer& localPlayer) {
    XMVECTOR worldPosVector = XMLoadFloat3(&worldPos);
    XMVECTOR transformed = XMVector3Transform(worldPosVector, localPlayer.viewMatrix);

    if (XMVectorGetW(transformed) < 0.1f) {
        return false;
    }

    transformed = XMVector3Transform(transformed, localPlayer.projectionMatrix);

    float x = (XMVectorGetX(transformed) / XMVectorGetW(transformed)) * 0.5f + 0.5f;
    float y = -(XMVectorGetY(transformed) / XMVectorGetW(transformed)) * 0.5f + 0.5f;

    screenPos.x = x * 1920;
    screenPos.y = y * 1080;
    screenPos.z = 0;

    return true;
}


void ESPRenderer::RenderESP(void* pvBits) {
    if (!Config::espEnabled) return;

    LocalPlayer& localPlayer = LocalPlayer::getInstance();

    for (const auto& player : ESPRenderer::players) {
        XMFLOAT3 screenPos;

        if (WorldToScreen(player.position, screenPos, localPlayer)) {

            if (Config::showBoundingBoxes) {
                float width = 50.0f;
                float height = 100.0f;

                int x = (int)(screenPos.x - width / 2.0f);
                int y = (int)(screenPos.y - height / 2.0f);
                int rectWidth = (int)(width);
                int rectHeight = (int)(height);

                if (x < 0 || y < 0 || x + rectWidth >= GetSystemMetrics(SM_CXSCREEN) || y + rectHeight >= GetSystemMetrics(SM_CYSCREEN)) {
                    continue;
                }

                for (int i = 0; i < rectHeight; ++i) {
                    for (int j = 0; j < rectWidth; ++j) {
                        if ((y + i) >= 0 && (y + i) < GetSystemMetrics(SM_CYSCREEN) &&
                            (x + j) >= 0 && (x + j) < GetSystemMetrics(SM_CXSCREEN)) {
                            int index = (y + i) * GetSystemMetrics(SM_CXSCREEN) + (x + j);
                            ((DWORD*)pvBits)[index] = 0xFFFF0000;
                        }
                    }
                }
            }
        }
    }
}







