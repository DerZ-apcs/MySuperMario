#include "../include/TextEffect.h"
#include <iostream>

TextEffect::TextEffect(std::string text, Vector2 pos, float duration, float delay):
	Effect(pos, delay, duration)
{
	this->text = text;
	this->duration = duration;
	this->delayed = delay;

	Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), font_size, 4 * outline_size);
	setSize(textSize);
	Outline = WHITE;
	TextColor = BLACK;
	setVel({ 0.f, -text_speed });
}
void TextEffect::setOutlineColor(Color color)
{
	this->Outline = color;
}

void TextEffect::setTextColor(Color color)
{
	this->TextColor = color;
}

void TextEffect::Update()
{
	const float deltaTime = GetFrameTime();
	setPosition({ position.x, getPosition().y + getVelY() * deltaTime});
	velocity.y += GRAVITY * deltaTime;

	Entity::Update();
	duration -= deltaTime;
	if (duration <= 0.f) setEntityDead();
	//Effect::Update();
}

void TextEffect::draw()
{
	if (text.empty())
		return;
	Font myFont = RESOURCE_MANAGER.getFont("WinterMinie");
	SetTextureFilter(myFont.texture, TEXTURE_FILTER_BILINEAR);

	DrawTextEx(myFont, text.c_str(), {getPosition().x, getPosition().y + outline_size}, font_size, 4 * outline_size, Outline);
	DrawTextEx(myFont, text.c_str(), { getPosition().x, getPosition().y - outline_size }, font_size, 4 * outline_size, Outline);
	DrawTextEx(myFont, text.c_str(), { getPosition().x + outline_size, getPosition().y }, font_size, 4 * outline_size, Outline);
	DrawTextEx(myFont, text.c_str(), { getPosition().x - outline_size, getPosition().y }, font_size, 4 * outline_size, Outline);

	DrawTextEx(myFont, text.c_str(), getPosition(), font_size, 4 * outline_size, TextColor);
}
