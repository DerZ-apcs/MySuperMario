#include "../include/GameEngine.h"
#include"../include/Character.h"
#include "../include/GUI.h"
#include "../include/Effect.h"
#include "../include/Enemy.h"
#include "../include/Coin.h"
#include "../include/Map.h"
#include "../include/Level.h"
#include "../include/Goomba.h"
#include "../include/Koopa.h"
#include "../include/ParaKoopa.h"
#include "../include/BobOmb.h"
#include "../include/Rex.h"
#include "../include/Bullet.h"
#include "../include/Flower.h"
#include "../include/Star.h"
#include "../include/Mushroom.h"
#include "../include/Moon.h"
#include "../include/FirePiranhaPlant.h"
#include "../include/JumpingPiranhaPlant.h"
#include "../include/PiranhaPlant.h"
#include "../include/Boss.h"
#include "../include/BoomBoom.h"
#include "../include/PeteyPiranha.h"
#include <iostream>

GameEngine* globalGameEngine = nullptr;

//GameEngine::GameEngine(float screenWidth, float screenHeight, Level& level, Character*& player)
//    : camera(screenWidth, screenHeight, 1.25f), level(&level), player(player) {
//    map.LoadFromJsonFile(level.getMapPath());
//    map.loadBackgroundTexture(level.getBackGroundName());
//    Vector2 Msize = map.getMapSize();
//    camera.loadRenderTexture(Msize);
//    // camera
//    if (!player) player = new Mario();
//    // test
//    //if (!player2) {
//    //    std::cout << "Allocating player2\n";
//    //    player2 = new Luigi();
//    //}
//    //else {
//    //    std::cout << "player2 already exists at: " << player2 << "\n";
//    //}
//
//    //if (player2) {
//    //    player2->setState(FALLING);
//    //    player2->setVel({ 0, 0 });
//    //    player2->setPosition({ 36, 400 });
//    //}
//   
//    multiplayers.clear();
//    multiplayers.push_back(player);
//    //multiplayers.push_back(player2);
//
//    blocks = map.getBlocks();
//    enemies = map.getEnemies();
//    items = map.getItems();
//    decor = map.getDecor();
//    isPaused = false;
//    this->time = 300;
//    resetTimer();
//    deltaTime = 0.f;
//    BackGroundPos = { {0, 0}, {(float)GetScreenWidth(), 0}, {(float)GetScreenWidth() * 2, 0} };
//    /*for (int i = 0; i < 10; i++) {
//        Coin* coin = new Coin(STATIC_COIN, { (float)i * 50, 600 });
//        items.push_back(coin);
//    }*/
//    /*for (int i = 7; i < 10; i++) {
//        Goomba* goomba = new Goomba({(float) 100 * i, 300 }, RESOURCE_MANAGER.getTexture("Goomba_RIGHT_0"));
//        goomba->setState(FALLING);
//        enemies.push_back(goomba);
//    }*/
//    /*for (int i = 9; i <= 10; i++) {
//        FlyingGoomba* flyingGoomba = new FlyingGoomba({ (float)50 * i, 300 }, RESOURCE_MANAGER.getTexture("FlyingGoomba_LEFT_0"));
//        flyingGoomba->setState(FALLING);
//        enemies.push_back(flyingGoomba);
//    }*/

//

//    //Bullet* bullet1 = new Bullet({ 1000, 400 }, RESOURCE_MANAGER.getTexture("Bullet_LEFT_0"), LEFT);
//    //enemies.push_back(bullet1);
//    //FireBullet* bullet2 = new FireBullet({ 1600, 500 }, RESOURCE_MANAGER.getTexture("Bullet_LEFT_0"), LEFT);
//    //enemies.push_back(bullet2);
//    //Bullet* bullet3 = new Bullet({ 1000, 600 }, RESOURCE_MANAGER.getTexture("Bullet_LEFT_0"), LEFT);
//    //enemies.push_back(bullet3);
//

//    //// test brick
//    //for (int i = 1; i < 10; i++) {
//    //    Brick* brick = new Brick(Vector2{ (float)i * 32, 700 }, Vector2{ 32, 32 }, "Brick_0");
//    //    blocks.push_back(brick);
//    //}
//    //// test coin block
//    //for (int i = 1; i < 10; i++) {
//    //    CoinBlock* coinBlock = new CoinBlock({ (float)i * 32, 550 }, "TILE_110", 4);
//    //    blocks.push_back(coinBlock);
//    //}
//    //

//}

GameEngine::GameEngine(float screenWidth, float screenHeight, Level& level, std::vector<std::unique_ptr<Character>>* multiplayers):
    camera(screenWidth, screenHeight, 1.25f), level(&level), multiplayers(multiplayers)
{
	globalGameEngine = this;
    map.LoadFromJsonFile(level.getMapPath());
    map.loadBackgroundTexture(level.getBackGroundName());
    Vector2 Msize = map.getMapSize();
    camera.loadRenderTexture(Msize);

    //blocks = map.getBlocks();
	tileGrid = map.getTileGrid();
    enemies = map.getEnemies();
    items = map.getItems();
    decor = map.getDecor();
	covers = map.getCovers();
	secretAreas = map.getSecretAreas();
    isPaused = false;
    this->time = 300;
    resetTimer();
    deltaTime = 0.f;
    BackGroundPos = { {0, 0}, {(float)GetScreenWidth(), 0}, {(float)GetScreenWidth() * 2, 0} };

    //ItemBlock* itemblock1 = new ItemBlock({ 100, 800 }, MUSHROOM, 0);
    //ItemBlock* itemblock2 = new ItemBlock({ 132, 800 }, STAR, 0);
    //ItemBlock* itemblock3 = new ItemBlock({ 164, 800 }, FLOWER, 0);
    //blocks.push_back(itemblock1);
    //blocks.push_back(itemblock2);
    //blocks.push_back(itemblock3);
    
    for (int i = 0; i < 10; i++) {
        Coin* coin = new Coin(STATIC_COIN, { (float)i * 50, 600 });
        items.push_back(coin);
    }

    //Rex* rex = new Rex({ 400, 500 }, RESOURCE_MANAGER.getTexture("Rex_LEFT_0"));
    //rex->setState(FALLING);
    //enemies.push_back(rex);

    //FirePiranhaPlant* plant = new FirePiranhaPlant({ 432, 710 }, RESOURCE_MANAGER.getTexture("PiranhaPlant_CLOSED"));
    //enemies.push_back(plant);

 //   Koopa* koopa = new YellowKoopa({ 100, 500 }, RESOURCE_MANAGER.getTexture("YellowKoopa_LEFT_0"));
 //   enemies.push_back(koopa);
	//enemies.push_back(new GreenKoopa({ 200, 500 }, RESOURCE_MANAGER.getTexture("GreenKoopa_LEFT_0")));
	//enemies.push_back(new RedKoopa({ 300, 500 }, RESOURCE_MANAGER.getTexture("RedKoopa_LEFT_0")));
   //enemies.push_back(new FlyingGoomba({ 250, 600 }, RESOURCE_MANAGER.getTexture("FlyingGoomba_LEFT_0")));
   //enemies.push_back(new Goomba({ 200, 500 }, RESOURCE_MANAGER.getTexture("Goomba_LEFT_0")));
   // enemies.push_back(new BoomBoom({300,200}, nullptr));
   //enemies.push_back(new Rex({ 300, 500 }, RESOURCE_MANAGER.getTexture("Rex_LEFT_0")));
	//enemies.push_back(new PeteyPiranha({ 300, 500 }, nullptr);
	enemies.push_back(new JumpingPiranhaPlant({ 300, 700 }, RESOURCE_MANAGER.getTexture("PiranhaPlant_JUMP_UP_0")));
}


GameEngine::~GameEngine() {
    for (size_t i = 0; i < enemyFireball.size(); i++)
        delete enemyFireball[i];
    for (size_t i = 0; i < enemies.size(); i++)
        delete enemies[i];
    for (size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }
    for (size_t i = 0; i < decor.size(); ++i) {
        delete decor[i];
    }
    for (size_t i = 0; i < effects.size(); ++i) {
        delete effects[i];
    }
    //for (size_t i = 0; i < blocks.size(); ++i) {
    //    delete blocks[i];
    //}
    for (size_t i = 0; i < tileGrid.size(); i++) {
        for (size_t j = 0; j < tileGrid[i].size(); j++) {
            delete tileGrid[i][j];
        }
    }
    for (size_t i = 0; i < covers.size(); i++) {
        delete covers[i];
    }
    //multiplayers.clear();
    enemyFireball.clear();
    //blocks.clear();
    tileGrid.clear();
    enemies.clear();
    items.clear();
    effects.clear();
    decor.clear();
}

void GameEngine::addScore(int amount) {
    for (auto& p : *multiplayers)
        p->setScores(p->getScores() + amount);
}

void GameEngine::addEnemyFireBall(EnemyFireBall* fireball) {
    this->enemyFireball.push_back(fireball);
}

void GameEngine::addEnemy(Enemy* enemy)
{
    this->enemies.push_back(enemy);
}

void GameEngine::addEffect(Effect* effect)
{
    this->effects.push_back(effect);
}

void GameEngine::addItem(Item* item)
{
    this->items.push_back(item);
}

// update
void GameEngine::update()
{
    if ((*multiplayers).empty()) return;
    if ((*multiplayers)[0] == nullptr) return;

    // for debug mode
    if (IsKeyPressed(KEY_O)) {
		SETTING.setDebugMode(!SETTING.getDebugMode());
    }

	Rectangle cameraView = camera.getViewRect();
    float margin = 120.0f; // Margin for camera view
    auto isInView = [&](float x, float y, float w = 32, float h = 32) {
        return CheckCollisionRecs(cameraView, { x - margin, y - margin, w + 2 * margin, h + 2 * margin });
    };

    if (IsKeyPressed(KEY_ENTER) || GUI::setting_is_pressed) {
        if (GUI::setting_is_pressed)
            GUI::setting_is_pressed = false;
        isPaused = !isPaused;
        if (died)
        {
            if (RESOURCE_MANAGER.isPlayingSound("lost_life.wav"))
                RESOURCE_MANAGER.stopSound("lost_life.wav");
            died = false;
            for (auto& p : *multiplayers) {
                p->setLostLife(false);
                p->resetInGame();
            }
            resetGame();
            resetTimer();
        }
        else if (isPaused) {
            if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("pause.wav");
        }
    }
    if (GUI::restart_is_pressed) {
        GUI::restart_is_pressed = false;
        for (auto& p : *multiplayers) {
            p->reset();
        }
        resetGame();
        resetTimer();
    }
    // let the pause and clear screen idling
    if (isPaused || cleared) {
        return;
    }
    // set Time 
    const float deltaTime = GetFrameTime();
    this->time -= deltaTime;

    // update background

    for (int i = 0; i < 3; i++) {
        // wrap from left to far most right
        float farX = 0;
        for (auto& p : *multiplayers)
            farX = max(p->getX(), farX);
        if (BackGroundPos[i].x + map.BgWidth <= farX - map.BgWidth / 2.0f) {
            float maxX = BackGroundPos[0].x;
            for (int j = 1; j < 3; j++) {
                if (BackGroundPos[j].x > maxX) maxX = BackGroundPos[j].x;
            }
            BackGroundPos[i].x = maxX + map.BgWidth;
        }
        // wrap from right to left
        float nearX = INT_MAX;
        for (auto& p : *multiplayers)
            nearX = min(nearX, p->getX());
        if (BackGroundPos[i].x + map.BgWidth / 2.0f >= nearX + map.BgWidth * 2) {
            float minX = BackGroundPos[i].x;
            for (int j = 1; j < 3; j++) {
                if (BackGroundPos[j].x < minX) minX = BackGroundPos[j].x;
            }
            BackGroundPos[i].x = minX - map.BgWidth;
        }
    }
	// enemy fireball update
	for (auto* ef : enemyFireball) {
		if (!isInCameraView(ef->getRect()))
			continue; // skip drawing this fireball
        if (ef->isDead() || ef->isMaxTime()) {
            delete ef;
            enemyFireball.erase(std::remove(enemyFireball.begin(), enemyFireball.end(), ef), enemyFireball.end());
            continue; // skip to next iteration
        }
        else 
			ef->Update();
	}

    // blocks
    for (size_t i = 0; i < tileGrid.size(); i++) {
        for (size_t j = 0; j < tileGrid[0].size(); j++) {
            Blocks* block = tileGrid[i][j];
            if (block == nullptr) continue;
			if (!isInCameraView(block->getRect()))
				continue; // skip drawing this block
            if (block->isDead()) {
                delete block;
                tileGrid[i][j] = nullptr;
            }
            else {
                block->Update();
            }
        }
    }
    // item
    for (auto* item : items) {
        if (!isInCameraView(item->getRect())) 
            continue; // skip drawing this item
        if (item->isDead()) {
            delete item;
            items.erase(std::remove(items.begin(), items.end(), item), items.end());
        }
        else
            item->Update();
    }
    // effect
	for (auto* ef : effects) {
		if (!isInCameraView(ef->getRect()))
			continue; // skip drawing this effect
		if (ef->isDead()) {
			delete ef;
			effects.erase(std::remove(effects.begin(), effects.end(), ef), effects.end());
		}
		else
			ef->Update();
	}
    // enemies
    for (auto* e : enemies) {
        if (!e || !isInCameraView(e->getRect()))
            continue;
        // skip drawing this enemy
        if (e->isDead()) {
            delete e;
            enemies.erase(std::remove(enemies.begin(), enemies.end(), e), enemies.end());
        }
        else
            e->Update();
    }

    // player udpate
        // handle input
    for (int i = 0; i < (*multiplayers).size(); ++i) {
        if ((*multiplayers)[i] != nullptr) {
            (*multiplayers)[i]->HandleInput(
                controlBindings[i].left,
                controlBindings[i].right,
                controlBindings[i].up,
                controlBindings[i].down,
                controlBindings[i].fire
            );
            (*multiplayers)[i]->Update();
        }
        else std::cout << "multiplayers[" << i << "] is nullptr!\n";
    }

    // all collision
    handleCollision();

    // camera update
    if ((*multiplayers).size() == 2) {
        camera.update((*multiplayers)[0]->getX(), (*multiplayers)[0]->getY(),
            (*multiplayers)[1]->getX(), (*multiplayers)[1]->getY());
    }
    else camera.update((*multiplayers)[0]->getX(), (*multiplayers)[0]->getY());
}

void GameEngine::handleCollision() {    
    // tiles (collision with character)

    CollisionInterface CollI;

    // for player
    for (auto& p : *multiplayers) {
        Vector2 pos = p->getPosition();
        auto nearbyBlocks = getNearbyBlocks(pos, 2);
        for (Blocks* b : nearbyBlocks) {
            if (b == nullptr) continue;
            CollI.HandleCollision(p.get(), b);
        }
		for (auto& fireball : *p->getFireBalls()) {
			auto nearby = getNearbyBlocks(fireball->getPosition(), 2);
			for (Blocks* b : nearby) {
				if (b == nullptr) continue;
				CollI.HandleCollision(fireball, b);
			}
		}
    }

    // enemies
    for (auto& enemy : enemies) {
        auto nearby = getNearbyBlocks(enemy->getPosition(), 2);
        for (Blocks* b : nearby)
            CollI.HandleCollision(enemy, b);
    }
    // items    
    for (auto& item : items) {
        auto nearby = getNearbyBlocks(item->getPosition(), 2);
        for (Blocks* b : nearby)
            CollI.HandleCollision(item, b);
    }   
	// enemy fireball
	for (size_t i = 0; i < enemyFireball.size(); i++) {
		auto nearby = getNearbyBlocks(enemyFireball[i]->getPosition(), 2);
		for (Blocks* b : nearby) {
			CollI.HandleCollision(enemyFireball[i], b);
		}
	}

    // player vs enemy
    for (auto& p : *multiplayers) {
        for (auto& e : enemies)
            CollI.HandleCollision(p.get(), e);
        for (auto& fireball : *p->getFireBalls()) {
            for (auto& e : enemies)
                CollI.HandleCollision(fireball, e);
        }
    }

    // Player vs Items
    for (auto& p : *multiplayers)
        for (auto& item : items)
            CollI.HandleCollision(p.get(), item);
    // Enemy fireball ↔ player
    for (auto& ef : enemyFireball)
        for (auto& p : *multiplayers)
            CollI.HandleCollision(ef, p.get());
}
// draw
void GameEngine::draw()
{
    camera.beginDrawing();
    ClearBackground(SKYBLUE);

    map.drawBackGround(camera.getSize(), camera.getScale());
    //map.drawMap();
   
    bool lostLife = false;
    for (auto& p : *multiplayers) {
        if (!p) return;
        lostLife = (lostLife == true || p->isLostLife());
    }
    bool drawCover = true;
    
    for (Entity* dec : decor) {
		if (!dec || !isInCameraView(dec->getRect())) continue;
		dec->draw();
    }

    // enemy fireball draw
    for (auto* ef : enemyFireball) {
		if (!ef || !isInCameraView(ef->getRect())) 
			continue; // skip drawing this fireball
        ef->draw();
    }
	// enemy draw
    for (auto* e : enemies) {
        if (!e || !isInCameraView(e->getRect()))
            continue; // skip drawing this enemy
		e->draw();
    }
    Boss* currentBoss = nullptr;
    // Lặp qua danh sách kẻ thù để tìm boss
    for (auto* enemy : enemies) {
        if (enemy && !enemy->isDying() && enemy->getEnemyType() == ENEMY_TYPE::BOSS) {
            // Nếu đúng, ép kiểu (cast) về con trỏ Boss*
            currentBoss = dynamic_cast<Boss*>(enemy);
            if (currentBoss) {
                break; // Tìm thấy boss, thoát khỏi vòng lặp
            }
        }
    }
	GUI::drawBossHealthBar(currentBoss);

    // tile draw
	for (size_t i = 0; i < tileGrid.size(); i++) {
		for (size_t j = 0; j < tileGrid[i].size(); j++) {
			if (tileGrid[i][j] != nullptr) {
                auto* block = tileGrid[i][j];
                if (!isInCameraView(block->getRect()))
                    continue;
                block->draw();
			}
		}
	}
    // draw the characters
    for (size_t i = 0; i < (*multiplayers).size(); i++) {
        (*multiplayers)[i]->draw();

        if ((*multiplayers).size() > 1) {
            std::string label = "P" + std::to_string(i + 1);
            Font font = RESOURCE_MANAGER.getFont("WinterMinie");
            float fontSize = 20.f;
            Vector2 pos = (*multiplayers)[i]->getPosition();
            Vector2 size = (*multiplayers)[i]->getSize();
            Vector2 textSize = MeasureTextEx(font, label.c_str(), fontSize, 1.0f);
            Vector2 textPos = {
                pos.x + size.x / 2 - textSize.x / 2,
                pos.y - textSize.y - 10
            };
            DrawTextPro(font, label.c_str(), textPos, { 0, 0 }, 0.f, fontSize, 1.0f, BLACK);
        }

        for (auto& area : secretAreas) {
            if (CheckCollisionPointRec((*multiplayers)[i]->getPosition(), area)) {
                drawCover = false;
                break;
            }
        }
    }
    // cover
    if (drawCover == true) {
		for (auto* cover : covers) {
			if (!cover || !isInCameraView(cover->getRect()))
				continue; // skip drawing this cover
			cover->draw();
		}
    }
    // item draw
    for (auto* item : items) {
		if (!item || !isInCameraView(item->getRect())) 
			continue; // skip drawing this item
        item->draw();
    }
    // effects draw
    for (auto* ef : effects) {
		if (!ef || !isInCameraView(ef->getRect()))
			continue; // skip drawing this effect
        ef->draw();
    }
    //Rectangle r = camera.getViewRect();
    //DrawRectangleLines(r.x, r.y, r.width, r.height, RED);

    camera.endDrawing();

    BeginDrawing();

    camera.render();


    if (!lostLife)
        if ((*multiplayers).size() == 1)
            GUI::drawStatusBar((*multiplayers)[0].get());
        else if ((*multiplayers).size() >= 1)
            GUI::drawStatusBar((*multiplayers));

    if (isPaused) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
        if (cleared) {
            GUI::drawLevelClear();
        }
        else if (gameover) {
            GUI::drawGameOverScreen();
        }
        else if (died)
            GUI::drawDeathScreen();
        else {
            GUI::drawPauseMenu();
            if (GUI::sound_is_pressed) {
                GUI::sound_is_pressed = false;
                if (SETTING.isMusicEnabled()) {
                    SETTING.setMusic(false);
                }
                else SETTING.setMusic(true);
            }
        }
    }

    EndDrawing();

}

// run
bool GameEngine::run() {
    RESOURCE_MANAGER.stopCurrentMusic();
    RESOURCE_MANAGER.playMusic(level->getMusic());
    // load and play the new music

    // second game loop (main game loop)
    while (!WindowShouldClose()) {
        if (SETTING.isMusicEnabled()) {
            UpdateMusicStream(RESOURCE_MANAGER.getMusic(level->getMusic()));
        }

        update();
        ClearBackground(RAYWHITE);
        draw();
        
        if (cleared == true && isPaused == false) {
            RESOURCE_MANAGER.stopCurrentMusic();
            RESOURCE_MANAGER.playMusic("MUSIC_1");
            return true;
        }

        if (gameover && !isPaused) break;
        if (GUI::home_is_pressed) {
            GUI::home_is_pressed = false;
            break;
        }

        for (auto& p : *multiplayers) {
            if (this->time <= 0) // outof time
                p->setLostLife(true);
            // set lost life for falling out of bound
            if (p->getY() > getBound().y && p->getPhase() != Phase::CLEARLEVEL_PHASE)
                p->setLostLife(true);
            // clear level
            if (!p->getExitLevel() && p->getX() >= map.getMapSize().x - 100.f && p->getState() == ON_GROUND) { // clear level (when character enter near the end of level)
                p->setVictory(true);
                p->setVel({ 0, 0 });
                RESOURCE_MANAGER.stopCurrentMusic();
                if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("level_clear.wav");
            }
            if ((p->getExitLevel()) && (p->getPhase() != Phase::CLEARLEVEL_PHASE)) {
                p->setPhase(Phase::CLEARLEVEL_PHASE);
            }
            if (p->getX() >= map.getMapSize().x - 10 && p->getPhase() == CLEARLEVEL_PHASE) {
                cleared = true;
                isPaused = true;
                p->setVel({ 0, 0 });
            }
            else if (p->isLostLife() && p->getTop() > getBound().y) { // when finish the animation of dying (flying to the top)
                if (p->getLives() < 0) {
                    gameover = true;
                    isPaused = true;
                }
                else {
                    died = true;
                    isPaused = true;
                }
            }
            if (p->isLostLife()) { // set animation & sound when dying
                if (p->getPhase() != DEAD_PHASE) {
                    RESOURCE_MANAGER.stopCurrentMusic();
                    p->setPhase(DEAD_PHASE);
                    if (p->getLives() < 0) {
                        if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("game_over.wav");
                    }
                    else {
                        if (SETTING.isSoundEnabled()) RESOURCE_MANAGER.playSound("lost_life.wav");
                    }
                }
            }
        }

    } 
    RESOURCE_MANAGER.stopCurrentMusic();
    RESOURCE_MANAGER.playMusic("TITLE");
    return false;
}

string GameEngine::getCurrentMapName()
{
    return level->getName();
}

float GameEngine::getGlobalTime() const 
{
    return deltaTime;
}

float GameEngine::getRemainingTime() const
{
    return this->time;
}

float GameEngine::resetTimer()
{
    this->time = 300;
    return 300.f;
}

bool GameEngine::isOver() const
{
    return gameover;
}

void GameEngine::resetGame()
{
    for (size_t i = 0; i < enemyFireball.size(); i++) {
        delete enemyFireball[i];
    }
    for (size_t i = 0; i < blocks.size(); ++i) {
        delete blocks[i];
    }
	for (size_t i = 0; i < tileGrid.size(); i++) {
		for (size_t j = 0; j < tileGrid[i].size(); j++) {
			delete tileGrid[i][j];
		}
	}
    for (size_t i = 0; i < enemies.size(); ++i) {
        delete enemies[i];
    }
    for (size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }
    for (size_t i = 0; i < decor.size(); ++i) {
        delete decor[i];
    }
    for (size_t i = 0; i < effects.size(); ++i) {
        delete effects[i];
    }
    for (size_t i = 0; i < covers.size(); i++) {
        delete covers[i];
    }

    enemyFireball.clear();
    //blocks.clear();
    tileGrid.clear();
    enemies.clear();
    items.clear();
    effects.clear();
    decor.clear();
    covers.clear();
    secretAreas.clear();
    for (auto& p : *multiplayers)
        p->getFireBalls()->clear();
    map.clear();

    RESOURCE_MANAGER.stopCurrentMusic();
    RESOURCE_MANAGER.playMusic(level->getMusic());
    map.LoadFromJsonFile(level->getMapPath());
    map.loadBackgroundTexture(level->getBackGroundName());
    //blocks = map.getBlocks();
	tileGrid = map.getTileGrid();
    enemies = map.getEnemies();
    items = map.getItems();
    decor = map.getDecor();
    covers = map.getCovers();
    secretAreas = map.getSecretAreas();
    isPaused = false;
    this->time = 300;
    resetTimer();
}

Vector2 GameEngine::getBound()
{
    return map.getMapSize();
}

std::vector<std::unique_ptr<Character>>& GameEngine::getMultiplayers()
{
    return *multiplayers;
}

std::vector<Blocks*> GameEngine::getNearbyBlocks(Vector2 pos, int range)
{
    std::vector<Blocks*> nearbyBlocks;
    int tileX = pos.x / 32;
	int tileY = pos.y / 32;
	for (int x = tileX - range; x <= tileX + range; ++x) {
		for (int y = tileY - range; y <= tileY + range; ++y) {
			if (x >= 0 && x < tileGrid[0].size() && y >= 0 && y < tileGrid.size()) {
				Blocks* block = tileGrid[y][x];
				if (block != nullptr) nearbyBlocks.push_back(block);
			}
		}
	}
	return nearbyBlocks;
}

bool GameEngine::isInCameraView(Rectangle entityRect) const {
    Rectangle view = camera.getViewRect();
    return CheckCollisionRecs(view, entityRect);
}
