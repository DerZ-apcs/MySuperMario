#include "../include/Camera.h"
#include "../include/GameEngine.h"
template <typename T>
T Myclamp(T value, T minVal, T maxVal) {
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
	if (renderTexture.texture.id != 0) {
		UnloadRenderTexture(renderTexture);
	}
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
void GameCamera::update(float p1x, float p1y, float p2x, float p2y, float goalX, float goalY) {
    // Thêm biến để kiểm tra frame đầu tiên
    static bool isFirstFrame = true;
    static int frameCount = 0;

    // Compute center between two players
    float centerX = (p1x + p2x) / 2.0f;
    float centerY = (p1y + p2y) / 2.0f;
    // Detect sudden large changes (e.g., respawn/teleport)
    static float previousCenterX = centerX;
    static float previousCenterY = centerY;
    float deltaX = fabs(centerX - previousCenterX);
    float deltaY = fabs(centerY - previousCenterY);
    const float respawnThreshold = 300.0f; // Giảm từ 1500.0f xuống 500.0f để nhạy hơn
    // Distance between players
    float distanceX = fabs(p1x - p2x);
    float distanceY = fabs(p1y - p2y);
    // Add visual buffer to ensure players aren't on edge
    const float bufferX = 1000.0f;
    const float bufferY = 500.0f;
    // View size that would be needed to fit both players + buffer
    float requiredWidth = distanceX + bufferX;
    float requiredHeight = distanceY + bufferY;
    // Compute the scale needed to fit that into the camera dimensions
    float desiredScaleX = cameraWidth / requiredWidth;
    float desiredScaleY = cameraHeight / requiredHeight;
    float desiredScale = fmin(desiredScaleX, desiredScaleY);
    // Clamp scale to safe zoom levels
    const float minZoom = 0.85f;
    const float maxZoom = 1.6f;
    desiredScale = Myclamp(desiredScale, minZoom, maxZoom);
    // Smooth transition to new scale (lerp)
    const float zoomSmooth = 0.01f;
    scale = scale + (desiredScale - scale) * zoomSmooth;
    // Calculate actual scaled view size
    float scaledWidth = cameraWidth / scale;
    float scaledHeight = cameraHeight / scale;
    // Calculate dynamic goal weight based on distance to goal
    float distToGoalP1 = sqrt(pow(p1x - goalX, 2) + pow(p1y - goalY, 2));
    float distToGoalP2 = sqrt(pow(p2x - goalX, 2) + pow(p2y - goalY, 2));
    float minDistToGoal = fmin(distToGoalP1, distToGoalP2);
    // Enhanced goal weight logic: Full priority when very close to goal
    const float maxGoalDistance = 1500.0f;
    const float minGoalDistance = 500.0f;
    const float closeGoalThreshold = 300.0f; // Full focus when very close
    float goalWeight = 1.0f - Myclamp((minDistToGoal - minGoalDistance) / (maxGoalDistance - minGoalDistance), 0.0f, 1.0f);
    if (minDistToGoal < closeGoalThreshold) {
        goalWeight = 1.0f; // Force full focus on goal when very close
    }
    // Smooth the goalWeight transition
    static float smoothedGoalWeight = 0.0f;
    const float weightSmooth = 0.05f;
    smoothedGoalWeight += (goalWeight - smoothedGoalWeight) * weightSmooth;

    // Tắt trọng số mục tiêu trong 30 frame đầu tiên để tránh ảnh hưởng của goal
    if (frameCount < 30) {
        smoothedGoalWeight = 0.0f;
        frameCount++;
    }

    // Calculate target position with smoothed goal influence
    float targetX = centerX * (1.0f - smoothedGoalWeight) + goalX * smoothedGoalWeight;
    float targetY = centerY * (1.0f - smoothedGoalWeight) + goalY * smoothedGoalWeight;
    // Adjust camera position with buffer for goal
    float desiredCameraX = targetX - scaledWidth / 2.0f;
    float desiredCameraY = renderTexture.texture.height - (targetY + scaledHeight / 2.0f) + verticalOffset - 100;
    // Add buffer to ensure goal is visible on the right
    const float goalBufferX = 200.0f; // Adjust this to ensure goal is in view
    if (minDistToGoal < minGoalDistance) {
        desiredCameraX = Myclamp(goalX - scaledWidth + goalBufferX, 0.0f, renderTexture.texture.width - scaledWidth);
    }
    // Clamp desired position to within texture bounds
    desiredCameraX = Myclamp(desiredCameraX, 0.0f, renderTexture.texture.width - scaledWidth);
    desiredCameraY = Myclamp(desiredCameraY, 0.0f, renderTexture.texture.height - scaledHeight) - 100;
    // Handle respawn/teleport: Instantly reset camera to desired position
    if (deltaX > respawnThreshold || deltaY > respawnThreshold) {
        cameraX = desiredCameraX;
        cameraY = desiredCameraY;
        smoothedGoalWeight = 0.0f; // Reset goal weight
        // Reset previous center để tránh ảnh hưởng trạng thái cũ
        previousCenterX = centerX;
        previousCenterY = centerY;
    }
    else {
        // Giảm moveSmooth để camera di chuyển mượt hơn
        const float moveSmooth = 0.05f; // Giảm từ 0.1f xuống 0.05f
        cameraX += (desiredCameraX - cameraX) * moveSmooth;
        cameraY += (desiredCameraY - cameraY) * moveSmooth;
    }
    // Khởi tạo camera ở vị trí mong muốn trong frame đầu tiên
    if (isFirstFrame) {
        cameraX = desiredCameraX;
        cameraY = desiredCameraY;
        previousCenterX = centerX; // Khởi tạo previous center
        previousCenterY = centerY;
        isFirstFrame = false;
    }
    // Update previous center for next frame
    previousCenterX = centerX;
    previousCenterY = centerY;
    // Final clamp to ensure camera stays within bounds
    if (cameraX < 0) cameraX = 0;
    if (cameraX + scaledWidth > renderTexture.texture.width)
        cameraX = renderTexture.texture.width - scaledWidth;
    if (cameraY < 0) cameraY = 0;
    if (cameraY + scaledHeight > renderTexture.texture.height)
        cameraY = renderTexture.texture.height - scaledHeight;
}
//void GameCamera::update(float p1x, float p1y, float p2x, float p2y, float goalX, float goalY) {
//// Compute center between two players
//    float centerX = (p1x + p2x) / 2.0f;
//    float centerY = (p1y + p2y) / 2.0f;
//
//    // Detect sudden large changes (e.g., respawn/teleport)
//    static float previousCenterX = centerX;
//    static float previousCenterY = centerY;
//    float deltaX = fabs(centerX - previousCenterX);
//    float deltaY = fabs(centerY - previousCenterY);
//    const float respawnThreshold = 500.0f;
//
//    // Distance between players
//    float distanceX = fabs(p1x - p2x);
//    float distanceY = fabs(p1y - p2y);
//
//    // Add visual buffer to ensure players aren't on edge
//    const float bufferX = 1000.0f;
//    const float bufferY = 500.0f;
//
//    // View size that would be needed to fit both players + buffer
//    float requiredWidth = distanceX + bufferX;
//    float requiredHeight = distanceY + bufferY;
//
//    // Compute the scale needed to fit that into the camera dimensions
//    float desiredScaleX = cameraWidth / requiredWidth;
//    float desiredScaleY = cameraHeight / requiredHeight;
//    float desiredScale = fmin(desiredScaleX, desiredScaleY);
//
//    // Clamp scale to safe zoom levels
//    const float minZoom = 0.85f;
//    const float maxZoom = 1.6f;
//    desiredScale = Myclamp(desiredScale, minZoom, maxZoom);
//
//    // Smooth transition to new scale (lerp)
//    const float zoomSmooth = 0.01f;
//    scale = scale + (desiredScale - scale) * zoomSmooth;
//
//    // Calculate actual scaled view size
//    float scaledWidth = cameraWidth / scale;
//    float scaledHeight = cameraHeight / scale;
//
//    // Calculate dynamic goal weight based on distance to goal
//    float distToGoalP1 = sqrt(pow(p1x - goalX, 2) + pow(p1y - goalY, 2));
//    float distToGoalP2 = sqrt(pow(p2x - goalX, 2) + pow(p2y - goalY, 2));
//    float minDistToGoal = fmin(distToGoalP1, distToGoalP2);
//
//    // Enhanced goal weight logic: Full priority when very close to goal
//    const float maxGoalDistance = 1500.0f;
//    const float minGoalDistance = 500.0f;
//    const float closeGoalThreshold = 300.0f; // Full focus when very close
//    float goalWeight = 1.0f - Myclamp((minDistToGoal - minGoalDistance) / (maxGoalDistance - minGoalDistance), 0.0f, 1.0f);
//    if (minDistToGoal < closeGoalThreshold) {
//        goalWeight = 1.0f; // Force full focus on goal when very close
//    }
//
//    // Smooth the goalWeight transition
//    static float smoothedGoalWeight = 0.0f;
//    const float weightSmooth = 0.05f;
//    smoothedGoalWeight += (goalWeight - smoothedGoalWeight) * weightSmooth;
//
//    // Calculate target position with smoothed goal influence
//    float targetX = centerX * (1.0f - smoothedGoalWeight) + goalX * smoothedGoalWeight;
//    float targetY = centerY * (1.0f - smoothedGoalWeight) + goalY * smoothedGoalWeight;
//
//    // Adjust camera position with buffer for goal
//    float desiredCameraX = targetX - scaledWidth / 2.0f;
//    float desiredCameraY = renderTexture.texture.height - (targetY + scaledHeight / 2.0f) + verticalOffset - 100;
//
//    // Add buffer to ensure goal is visible on the right
//    const float goalBufferX = 200.0f; // Adjust this to ensure goal is in view
//    if (minDistToGoal < minGoalDistance) {
//        desiredCameraX = Myclamp(goalX - scaledWidth + goalBufferX, 0.0f, renderTexture.texture.width - scaledWidth);
//    }
//
//    // Clamp desired position to within texture bounds
//    desiredCameraX = Myclamp(desiredCameraX, 0.0f, renderTexture.texture.width - scaledWidth);
//    desiredCameraY = Myclamp(desiredCameraY, 0.0f, renderTexture.texture.height - scaledHeight) - 100;
//
//    // Handle respawn/teleport: Instantly reset camera to desired position
//    if (deltaX > respawnThreshold || deltaY > respawnThreshold) {
//        cameraX = desiredCameraX;
//        cameraY = desiredCameraY;
//        smoothedGoalWeight = 0.0f; // Reset goal weight to avoid goal influence post-respawn
//    }
//    else {
//        // Otherwise, smooth camera movement transition
//        const float moveSmooth = 0.05f;
//        cameraX += (desiredCameraX - cameraX) * moveSmooth;
//        cameraY += (desiredCameraY - cameraY) * moveSmooth;
//    }
//
//    // Update previous center for next frame
//    previousCenterX = centerX;
//    previousCenterY = centerY;
//
//    // Final clamp to ensure camera stays within bounds
//    if (cameraX < 0) cameraX = 0;
//    if (cameraX + scaledWidth > renderTexture.texture.width)
//        cameraX = renderTexture.texture.width - scaledWidth;
//    if (cameraY < 0) cameraY = 0;
//    if (cameraY + scaledHeight > renderTexture.texture.height)
//        cameraY = renderTexture.texture.height - scaledHeight;
//}

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
    Rectangle view = getViewRect();
    //DrawRectangleLines(view.x, view.y, view.width, view.height, RED);  // ✅ draw it here
    //DrawRectangle(view.x, view.y, view.width, view.height, ColorAlpha(RED, 0.2f));
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

Rectangle GameCamera::getViewRect() const
{
	float scaledWidth = cameraWidth / scale;
	float scaledHeight = cameraHeight / scale;
	float margin; // Margin for camera view

    if (globalGameEngine->getMultiplayers().size() == 1) {
		margin = 300; // Margin for single player
	}
	else 
		margin = 400; // Margin for multiplayer

    return Rectangle{
        cameraX - margin, // top-left x in world space
        cameraY - margin * 2, // top-left y in world space
        scaledWidth + margin * 2,
        scaledHeight + margin * 5 
	};
}


Vector2& GameCamera::getPos() const
{
    return Vector2{ cameraX, cameraY };
}

//------------------------

EditorCamera::EditorCamera() : position{ 0, 0 }, zoom(1.0f), isDragging(false) {}

void EditorCamera::beginDrawing() {
    BeginMode2D(GetCamera2D());
}

void EditorCamera::endDrawing() {
    EndMode2D();
}

void EditorCamera::handleInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        isDragging = true;
        dragStart = GetMousePosition();
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) && isDragging) {
        Vector2 mouseNow = GetMousePosition();
        Vector2 delta = Vector2Subtract(dragStart, mouseNow);
        position = Vector2Add(position, Vector2Scale(delta, 1.0f / zoom));
        dragStart = mouseNow;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE)) {
        isDragging = false;
    }

    float scroll = GetMouseWheelMove();
    if (scroll != 0) {
        zoom += scroll * 0.1f;
        if (zoom < 0.5f) zoom = 0.5f;
        if (zoom > 2.0f) zoom = 2.0f;
    }
}

Camera2D EditorCamera::GetCamera2D() const {
    return Camera2D{
        { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f },
        position,
        0.0f,
        zoom
    };
}

Vector2 EditorCamera::getWorldPos(Vector2 screenPos) const {
    Vector2 screenCenter = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    Vector2 offsetFromCenter = Vector2Subtract(screenPos, screenCenter);
    return Vector2Add(position, Vector2Scale(offsetFromCenter, 1.0f / zoom));
}

Vector2 EditorCamera::getPosition() const {
    return position;
}

float EditorCamera::getZoom() const {
    return zoom;
}

Rectangle EditorCamera::getViewRect() const {
    float viewWidth = GetScreenWidth() / zoom;
    float viewHeight = GetScreenHeight() / zoom;

    return {
        position.x - viewWidth / 2.0f,
        position.y - viewHeight / 2.0f,
        viewWidth,
        viewHeight
    };
}