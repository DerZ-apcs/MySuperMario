#ifndef BUTTON_H
#define BUTTON_H
#include <raylib.h>

class Button {
public:
	Button();
	Button(Vector2 pos, Vector2 size, Color normal, Color hovered);
	bool isHovered() const;
	bool isPressed() const;
	virtual void handle();
	virtual void draw();
	virtual void setPosition(const float& x, const float& y);
	virtual void setSize(const float& width, const float& height);
	Vector2 getSize() const;
	Vector2 getPosition() const;
	virtual void update();
	~Button();
protected:
	Vector2 m_position;
	Vector2 m_size;
	bool is_hovered = false;
	bool is_pressed = false;
	Color NormalColor;
	Color HoveredColor;
};
#endif