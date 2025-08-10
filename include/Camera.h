#ifndef CAMERA_H
#define CAMERA_H
#include <raylib.h>
#include <iostream>
#include <raymath.h>
#include "../include/json.hpp"
using nlohmann::json;

class GameEngine;

class GameCamera {
private:
	float cameraX;
	float cameraY;
	float targetX = 0.f;
	float targetY = 0.f;
	float cameraWidth;
	float cameraHeight;
	float verticalOffset = 200.f; // to make the ground up
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
	void loadCamera(const json& j);
	void saveCamera(json& j) const;

};

//------------

class EditorCamera {
private:
	Vector2 position; // world offset
	float zoom;
	bool isDragging;
	Vector2 dragStart;

public:
	EditorCamera();

	void beginDrawing();
	void endDrawing();
	Camera2D GetCamera2D() const;
	Vector2 getWorldPos(Vector2 screenPos) const; // Converts screen coordinates to world coordinates

	Vector2 getPosition() const;
	float getZoom() const;
	Rectangle getViewRect() const;

	void handleInput();
};

#endif