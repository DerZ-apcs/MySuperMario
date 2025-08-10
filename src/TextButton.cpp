#include "../include/TextButton.h"

Font* TextButton::SMW = nullptr;
Color darkerWhite = { 180, 180, 180, 255 };

TextButton::TextButton():
	TextButton({0, 0}, {0, 0}, "", SMW)
{
}

TextButton::TextButton(Vector2 pos, Vector2 size, std::string text):
	TextButton(pos, size, text, SMW)
{
}

TextButton::TextButton(Vector2 pos, Vector2 size, std::string text, Font* font):
	m_position(pos), m_size(size), text(text), font(font),
	is_hovered(false),
	is_pressed(false)
{
}
void TextButton::DrawTextWithOutline(Font* font, const std::string& text, Vector2 position, float fontSize, float spacing, Color textColor, Color outlineColor)
{
	if (!font) {
		std::cerr << "[ERROR] Font is not set for TextButton!" << std::endl;
		return;
	}
	// 1-pixel offset for outline
	const int offset = 3;

	// Draw outline (8 directions)
	DrawTextEx(*font, text.c_str(), { position.x - offset, position.y - offset }, fontSize, spacing, outlineColor);
	DrawTextEx(*font, text.c_str(), { position.x + offset, position.y - offset }, fontSize, spacing, outlineColor);
	DrawTextEx(*font, text.c_str(), { position.x - offset, position.y + offset }, fontSize, spacing, outlineColor);
	DrawTextEx(*font, text.c_str(), { position.x + offset, position.y + offset }, fontSize, spacing, outlineColor);
	DrawTextEx(*font, text.c_str(), { position.x, position.y - offset }, fontSize, spacing, outlineColor);
	DrawTextEx(*font, text.c_str(), { position.x, position.y + offset }, fontSize, spacing, outlineColor);
	DrawTextEx(*font, text.c_str(), { position.x - offset, position.y }, fontSize, spacing, outlineColor);
	DrawTextEx(*font, text.c_str(), { position.x + offset, position.y }, fontSize, spacing, outlineColor);

	// Draw main text on top
	DrawTextEx(*font, text.c_str(), position, fontSize, spacing, textColor);
}

bool TextButton::isHovered() const
{
	return is_hovered;
}

void TextButton::setHovered(bool hovered) {
	is_hovered = hovered;
}
bool TextButton::isPressed() const 
{
	return is_pressed;
}

void TextButton::handle() 
{

}

void TextButton::draw() 
{
	// Resize text button dynamically based on text
	if (!font) font = RESOURCE_MANAGER.getFont("SMW");
	if (!font) return; // avoid crash if even fallback fails

	if (font) {
		int fontSize = isHovered() ? 42 : 36;
		Color colorText = isHovered() ? WHITE : RAYWHITE;
		Vector2 textSize = MeasureTextEx(*font, text.c_str(), fontSize, 1);
		setSize(textSize.x + 20, 60);

		if (TextButton::SMW) {
			Vector2 textPos = {
				m_position.x + m_size.x / 2 - textSize.x / 2,
				m_position.y + m_size.y / 2 - textSize.y / 2
			};

			DrawTextWithOutline(TextButton::SMW, text.c_str(), textPos, fontSize, 1, colorText, BLACK);

		}
	}
}

void TextButton::setPosition(const float& x, const float& y)
{
	this->m_position.x = x;
	this->m_position.y = y;
}

void TextButton::setSize(const float& width, const float& height)
{
	this->m_size.x = width;
	this->m_size.y = height;
}

Vector2 TextButton::getSize() const
{
	return m_size;
}

Vector2 TextButton::getPosition() const
{
	return m_position;
}

void TextButton::update()
{
	is_hovered = CheckCollisionPointRec(GetMousePosition(), { m_position.x, m_position.y, m_size.x, m_size.y });
	if (is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		is_pressed = true;
	}
	else is_pressed = false;
}

void TextButton::setText(const std::string text)
{
	this->text = text;
}

std::string TextButton::getText() const
{
	return text;
}

TextButton::~TextButton()
{
}
