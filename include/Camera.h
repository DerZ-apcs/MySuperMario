#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <raylib.h>

class GameCamera {
private:
	float cameraX;
	float cameraY;
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
	void render() const;
	void beginDrawing();
	void endDrawing();
	void setScale(float newScale);
	Vector2& getSize() const;
	Vector2& getPos() const;
	float getScale() const;
};
#endif