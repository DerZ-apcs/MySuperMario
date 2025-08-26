#include "../include/BanzaiBill.h"

BanzaiBill::BanzaiBill(Vector2 pos, Texture2D tex):
	BanzaiBill(pos, tex, LEFT)
{
}

BanzaiBill::BanzaiBill(Vector2 pos, Texture2D texture, Direction direction):
	Bullet(pos, texture, direction)
{
	velocity.x = (direction == LEFT) ? -SPEED_BANZAIBILL : SPEED_BANZAIBILL;
	setSize({ 128, 128 });
	scores = 0.0f; // BanzaiBill không có điểm thưởng
	updateCollision();
}

BanzaiBill::~BanzaiBill()
{
}

ENEMY_TYPE BanzaiBill::getEnemyType() const
{
	return BANZAIBILL;
}

void BanzaiBill::UpdateTexture()
{
	if (isDead() || state == STATE_IS_DYING) {
		texture = RESOURCE_MANAGER.getTexture("BanzaiBill_Dead");
		return;
	}
	std::string dir = direction == RIGHT ? "_RIGHT" : "_LEFT";
	texture = RESOURCE_MANAGER.getTexture("BanzaiBill" + dir);
}

float BanzaiBill::getScores() const
{
	return 0.f;
}

void BanzaiBill::saveEntity(json& j) const
{
	Bullet::saveEntity(j);
	j["properties"] = json::array({
	{
		{ "name", "Name" },
		{ "type", "string" },
		{ "value", "Enemy" }
	},
	{
		{ "name", "Type" },
		{ "type", "string" },
		{ "value", "BanzaiBill"}
	}
		});
}
