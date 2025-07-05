#include "../include/Button.h"

Button::Button():
	Button({0, 0}, {100, 50}, DARKGRAY, LIGHTGRAY, "")
{
	
}

Button::Button(Vector2 pos, Vector2 size, Color normal, Color hovered, std::string text) :
	m_position(pos), m_size(size), NormalColor(normal), HoveredColor(hovered), text(text),
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
	setSize(MeasureText(this->text.c_str(), 30) * 2.0f, 60);
	Color cur = is_hovered ? HoveredColor : NormalColor;
	DrawRectangle(m_position.x, m_position.y, m_size.x, m_size.y, cur);
	Color colorText = is_hovered ? WHITE : BLACK;
	DrawText(this->text.c_str(), m_position.x + m_size.x / 2 - MeasureText(text.c_str(), 30) / 2.0f, m_position.y + m_size.y / 2 - 15, 30, colorText);
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
	if (is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		is_pressed = true;
	}
	else is_pressed = false;

}

void Button::setText(const std::string text)
{
	this->text = text;
}

Color Button::getNormalColor() const
{
	return NormalColor;
}

Color Button::getHoveredColor() const
{
	return HoveredColor;
}

std::string Button::getText() const
{
	return text;
}

Button::~Button()
{
}
