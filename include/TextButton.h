#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H	
// TextButton.h
#include <raylib.h>
#include <string>
#include "../include/Global.h"

class TextButton {
	friend class GUI;
public:
	TextButton();
	TextButton(Vector2 pos, Vector2 size, std::string text);
	TextButton(Vector2 pos, Vector2 size, std::string text, Font* font);
	static Font* SMW;
	bool isHovered() const;
	void setHovered(bool hovered);
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
	~TextButton();
	void setFont(Font* font) { this->font = font; }
	static void DrawTextWithOutline(Font* font, const std::string& text, Vector2 position, float fontSize, float spacing, Color textColor, Color outlineColor);
private:
	Font* font;
	Vector2 m_position;
	Vector2 m_size;
	bool is_hovered = false;
	bool is_pressed = false;
	std::string text;
};
#endif