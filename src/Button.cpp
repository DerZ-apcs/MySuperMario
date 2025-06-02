#include "../include/Button.h"

Button::Button():
	Button({0, 0}, {100, 50}, DARKGRAY, LIGHTGRAY)
{
	
}

Button::Button(Vector2 pos, Vector2 size, Color normal, Color hovered) :
	m_position(pos), m_size(size), NormalColor(normal), HoveredColor(hovered),
	is_hovered(false),
	is_pressed(false)
{
}


bool Button::isHovered() const
{
	return is_hovered;
}

bool Button::isPressed() const
{
	return is_pressed;
}

void Button::handle()
{
}

void Button::draw()
{
}

void Button::setPosition(const float& x, const float& y)
{
	this->m_position.x = x;
	this->m_position.y = y;
}

void Button::setSize(const float& width, const float& height)
{
	this->m_size.x = width;
	this->m_size.y = height;
}

Vector2 Button::getSize() const
{
	return m_size;
}

Vector2 Button::getPosition() const
{
	return m_position;
}

void Button::update()
{
	is_hovered = CheckCollisionPointRec(GetMousePosition(), { m_position.x, m_position.y, m_size.x, m_size.y });
	if (is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		is_pressed = true;
	}
	else is_pressed = false;

}

Button::~Button()
{
}
