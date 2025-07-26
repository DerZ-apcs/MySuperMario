// ParaKoopa.h
#ifndef PARA_KOOPA_H
#define PARA_KOOPA_H

#include "../include/Koopa.h"

class ParaKoopa : public Koopa {
protected:
    float jumpTimer;
public:
    ParaKoopa(Vector2 pos, Texture2D texture);
    virtual void Update() override = 0;
};

class ParaKoopaRed : public ParaKoopa {
public:
    ParaKoopaRed(Vector2 pos, Texture2D texture);
    void Update() override;
    void UpdateTexture() override;
};

class ParaKoopaBlue : public ParaKoopa {
public:
    ParaKoopaBlue(Vector2 pos, Texture2D texture);
    void Update() override;
    void UpdateTexture() override;
};

#endif // PARA_KOOPA_H
