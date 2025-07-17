#ifndef COIN_EFFECT_H
#define COIN_EFFECT_H

#include "../include/Effect.h"

class CoinEffect : public Effect {
private:
	static constexpr float coin_duration = 1.0f;

public:
	CoinEffect(Vector2 pos, float duration = coin_duration, float delay = 0.0f);
	CoinEffect(Vector2 pos, std::vector<Texture2D> animations, float duration = coin_duration, float delay = 0.0f);
	~CoinEffect() override = default;

	void Update() override;
	void UpdateTexture() override;
	void draw() override;

};

#endif // !COIN_EFFECT_H
