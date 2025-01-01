#include "../include/esp_renderer.h"
#include <DirectXMath.h>

using namespace DirectX;

float nearPlane = 0.1f;
float farPlane = 1000.0f;

//Projection Matrix
//XMMatrixPerspectiveFovLH(XMConvertToRadians(fovDegrees), aspectRatio, nearPlane, farPlane);


//View Matrix
XMMATRIX CreateViewMatrixFromYawPitch(const XMFLOAT3& cameraPosition, float yaw, float pitch) {
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

bool WorldToScreen(const Vector3& worldPos, Vector3& screenPos, const LocalPlayer& localPlayer) {
    XMFLOAT3 worldPosFloat3 = { worldPos.x, worldPos.y, worldPos.z };
    XMVECTOR transformed = XMVector3Transform(XMLoadFloat3(&worldPosFloat3), localPlayer.viewMatrix);

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

void ESPRenderer::RenderESP() {
    if (!Config::espEnabled) return;

    LocalPlayer& localPlayer = LocalPlayer::getInstance();

    for (const auto& player : ESPRenderer::players) {
        Vector3 screenPosHead, screenPosPelvis;
        if (WorldToScreen(player.position, screenPosHead, localPlayer) &&
            WorldToScreen(player.position, screenPosPelvis, localPlayer)) {

            if (Config::showBoundingBoxes) {
                float width = fabs(screenPosPelvis.x - screenPosHead.x);
                float height = fabs(screenPosPelvis.y - screenPosHead.y);

                struct Vertex {
                    float x, y, z, w;
                };

                Vertex vertices[4] = {
                    { screenPosHead.x - width, screenPosHead.y - height, 0.0f, 1.0f },
                    { screenPosHead.x + width, screenPosHead.y - height, 0.0f, 1.0f },
                    { screenPosHead.x + width, screenPosHead.y + height, 0.0f, 1.0f },
                    { screenPosHead.x - width, screenPosHead.y + height, 0.0f, 1.0f }
                };

                ESPRenderer::pContext->Draw(4, 0);
            }
        }
    }
}



