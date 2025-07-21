#include "../include/Camera.h"

template <typename T>
T clamp(T value, T minVal, T maxVal) {
    return std::max(minVal, std::min(value, maxVal));
}


GameCamera::GameCamera(float width, float height, float initialScale)
    : cameraWidth(width), cameraHeight(height), cameraX(0), cameraY(0), scale(initialScale) {
    renderTexture = LoadRenderTexture(0, 0);
}

GameCamera::~GameCamera() {
    UnloadRenderTexture(renderTexture);
}

void GameCamera::loadRenderTexture(Vector2 size)
{
    renderTexture = LoadRenderTexture(static_cast<int>(round(size.x)), static_cast<int>(round(size.y)));
}

void GameCamera::update(float characterX, float characterY) {
    float scaledWidth = cameraWidth / scale;
    float scaledHeight = cameraHeight / scale;

    cameraX = characterX - scaledWidth / 2;
    cameraY = renderTexture.texture.height - (characterY + cameraHeight / scale) + verticalOffset + 100 ;

    // Clamp the camera to ensure it stays within the map bounds
    if (cameraX < 0) cameraX = 0;
    if (cameraX + scaledWidth > renderTexture.texture.width)
        cameraX = renderTexture.texture.width - scaledWidth;
    if (cameraY < 0) cameraY = 0;
    if (cameraY + scaledHeight > renderTexture.texture.height)
        cameraY = renderTexture.texture.height - scaledHeight;
}

void GameCamera::update(float p1x, float p1y, float p2x, float p2y) {
    // Compute center between two players
    float centerX = (p1x + p2x) / 2.0f;
    float centerY = (p1y + p2y) / 2.0f;

    // Distance between players
    float distanceX = fabs(p1x - p2x);
    float distanceY = fabs(p1y - p2y);

    // Add visual buffer to ensure players aren't on edge
    const float bufferX = 300.0f;  // Increased for better spacing
    const float bufferY = 500.0f;

    // View size that would be needed to fit both players + buffer
    float requiredWidth = distanceX + bufferX;
    float requiredHeight = distanceY + bufferY;

    // Compute the scale needed to fit that into the camera dimensions
    float desiredScaleX = cameraWidth / requiredWidth;
    float desiredScaleY = cameraHeight / requiredHeight;
    float desiredScale = fmin(desiredScaleX, desiredScaleY);

    // Clamp scale to safe zoom levels
    // clamp target scale;
    const float minZoom = 0.85f;
    const float maxZoom = 1.6f;
    desiredScale = clamp(desiredScale, minZoom, maxZoom);

    // smooth transition to new scale (lerp)
    const float zoomSmooth = 0.02f;
    scale = scale + (desiredScale - scale) * zoomSmooth;

    // Calculate actual scaled view size
    float scaledWidth = cameraWidth / scale;
    float scaledHeight = cameraHeight / scale;

    // Center the camera
    cameraX = centerX - scaledWidth / 2.0f;
    cameraY = renderTexture.texture.height - (centerY + scaledHeight / 2.0f) /*+ verticalOffset + 100*/;

    // 9. Clamp target position to within texture bounds
    targetX = clamp(targetX, 0.0f, renderTexture.texture.width - scaledWidth);
    targetY = clamp(targetY, 0.0f, renderTexture.texture.height - scaledHeight);

    // 10. Smooth camera movement transition (main fix for jump jitter)
    const float moveSmooth = 0.05f;  // Try 0.05f for even smoother
    cameraX += (targetX - cameraX) * moveSmooth;
    cameraY += (targetY - cameraY) * moveSmooth;

    // Clamp camera to inside the texture bounds
    if (cameraX < 0) cameraX = 0;
    if (cameraX + scaledWidth > renderTexture.texture.width)
        cameraX = renderTexture.texture.width - scaledWidth;
    if (cameraY < 0) cameraY = 0;
    if (cameraY + scaledHeight > renderTexture.texture.height)
        cameraY = renderTexture.texture.height - scaledHeight;
}



void GameCamera::render() const {
    Rectangle sourceRec = {
        cameraX,
        cameraY,
        cameraWidth / scale,
        -cameraHeight / scale // Negative height to flip vertically
    };

    Rectangle destRec = {
        0, 0,                        // Render starting at the screen's top-left
        (float)GetScreenWidth(),     // Scale to fit the screen width
        (float)GetScreenHeight()     // Scale to fit the screen height
    };

    DrawTexturePro(renderTexture.texture, sourceRec, destRec, Vector2{ 0, 0 }, 0.0f, WHITE);
}

void GameCamera::beginDrawing() {
    BeginTextureMode(renderTexture);
    ClearBackground(RAYWHITE);
}

void GameCamera::endDrawing() {
    EndTextureMode();
}

void GameCamera::setScale(float newScale) {
    scale = newScale;
    if (scale < 0.1f) scale = 0.1f; // Prevent too small scale
}

Vector2& GameCamera::getSize() const
{
    return Vector2{cameraWidth, cameraHeight};
}

float GameCamera::getScale() const
{
    return scale;
}

Vector2& GameCamera::getPos() const
{
    return Vector2{ cameraX, cameraY };
}


