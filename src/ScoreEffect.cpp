#include "../include/ScoreEffect.h"

ScoreEffect::ScoreEffect(Texture2D tex, Vector2 pos, float duration, float delay):
	Effect(pos, delay, duration), tex(tex)
{
	this->duration = duration;
	this->delayed = delay;
	velocity = { 0.f, -score_speed };
}

void ScoreEffect::setTexture(Texture2D tex)
{
	this->tex = tex;
}
void ScoreEffect::Update()
{
	Entity::Update();
	const float deltaTime = GetFrameTime();
	setPosition({ position.x, getPosition().y + getVelY() * deltaTime });
	velocity.y += GRAVITY * deltaTime * 0.1;
	duration -= deltaTime;
	if (duration <= 0.f) setEntityDead();
}
void ScoreEffect::draw()
{
	if (tex.id == 0) {
		return;
	}
	DrawTexturePro(tex, { 0, 0, (float)tex.width, (float)tex.height },
		{getX(), getY(), (float)16 * 1.3, (float)14 * 1.3}, {0, 0}, 0.f, WHITE);
}