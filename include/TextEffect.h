#ifndef TEXTEFFECT_H
#define TEXTEFFECT_H
#include "../include/Effect.h"

class TextEffect : public Effect {
private:
	std::string text;
	Color Outline;
	Color TextColor;

	static constexpr float text_duration = 0.7f;
	const float text_speed = 400.f;
	static constexpr float font_size = 16.f;
	static constexpr float outline_size = 2.f;
public:
	TextEffect(std::string text, Vector2 pos, float duration = text_duration, float delay = 0.f);
	void setOutlineColor(Color color);
	void setTextColor(Color color);
	void Update() override;
	void draw() override;
};

#endif