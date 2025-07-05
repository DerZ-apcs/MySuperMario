#ifndef BUTTON_H
#define BUTTON_H
#include <raylib.h>
#include <string>

class Button {
public:
	Button();
	Button(Vector2 pos, Vector2 size, Color normal, Color hovered, std::string text);
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
	Color getNormalColor() const;
	Color getHoveredColor() const;
	std::string getText() const;
	~Button();
private:
	Vector2 m_position;
	Vector2 m_size;
	bool is_hovered = false;
	bool is_pressed = false;
	Color NormalColor;
	Color HoveredColor;
	std::string text;
};
#endif