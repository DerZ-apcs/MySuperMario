#ifndef CAMERA_H
#define CAMERA_H
#include <raylib.h>
#include <iostream>
class GameEngine;


class GameCamera {
private:
	float cameraX;
	float cameraY;
	float targetX = 0.f;
	float targetY = 0.f;
	float cameraWidth;
	float cameraHeight;
	float verticalOffset = 100.f; // to make the ground up
	float scale; // Scaling factor
	RenderTexture2D renderTexture;
public:
	GameCamera(float width, float height, float initialScale = 1.0f);
	~GameCamera();
	void loadRenderTexture(Vector2 size);
	void update(float characterX, float characterY);
	void update(float p1x, float p1y, float p2x, float p2y);
	void render() const;
	void beginDrawing();
	void endDrawing();
	void setScale(float newScale);
	Vector2& getSize() const;
	Vector2& getPos() const;
	float getScale() const;
	Rectangle getViewRect() const;
};

#endif