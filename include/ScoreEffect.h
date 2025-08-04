#ifndef SCOREEFFECT_H
#define SCOREEFFECT_H
#include "../include/Effect.h"
#include <unordered_map>

class ScoreEffect : public Effect {
private:
	Texture2D tex;
	//std::unordered_map<Texture2D, std::string> scores;
	static constexpr float score_duration = 0.7f;
	const float score_speed = 50.f;
public:
	ScoreEffect(Texture2D tex, Vector2 pos, float duration = score_duration, float delay = 0.f);
	void setTexture(Texture2D tex);

	void Update() override;
	void draw() override;
};

#endif