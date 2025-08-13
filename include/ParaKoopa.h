// ParaKoopa.h
#ifndef PARA_KOOPA_H
#define PARA_KOOPA_H

#include "../include/Koopa.h"

class ParaKoopa : public Koopa {
protected:
    float jumpTimer;
    bool hasWings;
    PARAKOOPA_TYPE paraKoopaType;
public:
    ParaKoopa(Vector2 pos, Texture2D texture);
    float getScores() const override;
    ENEMY_TYPE getEnemyType() const override;
    virtual void Update() override;
	void draw() override;
	void UpdateTexture() override;
	void stomped() override;
    void loadEntity(const json& j) override;
    void saveEntity(json& j) const override;
};

// different update for different ParaKoopa types
class ParaKoopaRed : public ParaKoopa {
public:
    ParaKoopaRed(Vector2 pos, Texture2D texture);
    void Update() override;
};

class ParaKoopaBlue : public ParaKoopa {
public:
    ParaKoopaBlue(Vector2 pos, Texture2D texture);
    void Update() override;
};
class ParaKoopaGreen : public ParaKoopa {
public:
    ParaKoopaGreen(Vector2 pos, Texture2D texture);
    void Update() override;
};
class ParaKoopaYellow : public ParaKoopa {
public:
    ParaKoopaYellow(Vector2 pos, Texture2D texture);
    void Update() override;
};
#endif // PARA_KOOPA_H