//#include "../include/Shockwave.h"
//
//Shockwave::Shockwave(Vector2 pos, Vector2 dir)
//    : Entity(pos, { 32, 16 }, { dir.x * 400.0f, 0 }, dir.x > 0 ? RIGHT : LEFT, ON_GROUND)
//{
//    setTexture(RESOURCE_MANAGER.getTexture("shockwave_effect"));
//    setGravityAvailable(false);
//    lifetime = 0.5f; 
//}
//
//void Shockwave::Update() {
//    Entity::Update();
//    lifetime -= GetFrameTime();
//    if (lifetime <= 0) {
//        setEntityDead();
//    }
//}