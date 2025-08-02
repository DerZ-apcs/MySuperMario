#ifndef BUTTON_H
#define BUTTON_H
#include <raylib.h>
#include <string>
#include "../include/Global.h"

class Button {
public:
	Button();
	Button(Vector2 pos, Vector2 size, Texture2D texture = RESOURCE_MANAGER.getTexture("BOARD1"), std::string text = "");
	bool isHovered() const;
	bool isPressed() const;
	void handle();
	void draw();
	void setPosition(const float& x, const float& y);
	void setSize(const float& width, const float& height);
	Vector2 getSize() const;
	Vector2 getPosition() const;
	void update();
	void setText(const std::string text);
	std::string getText() const;
	~Button();
	void setTexture(Texture2D tex) { texture = tex; }
private:
	Texture2D texture;
	Vector2 m_position;
	Vector2 m_size;
	bool is_hovered = false;
	bool is_pressed = false;
	std::string text;
};
#endif