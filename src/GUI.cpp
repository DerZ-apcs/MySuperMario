#include "../include/GUI.h"
#include"../include/Character.h"
#include "../include/GameEngine.h"

Texture2D GUI::coinTexture;
Texture2D GUI::heartTexture;
Texture2D GUI::multiplicationSign;
Texture2D GUI::board;
Texture2D GUI::largeBoard;
Texture2D GUI::board1;
Texture2D GUI::board2;
Texture2D GUI::board3;
Texture2D GUI::restart;
Texture2D GUI::home;
Texture2D GUI::setting;
Texture2D GUI::sound_on;
Texture2D GUI::sound_off;


void GUI::drawStatusBar(const Character* player) {
    Rectangle dest, source;

    //Draw board
    dest = { 20.f, 20.f, 1138.f / 4.f, 397.f / 4.f };
    source = { 0, 0, (float)board1.width, (float)board1.height };
    DrawTexturePro(board1, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    dest = { 20.f, 120.f, 1138.f / 4.f, 397.f / 4.f };
    DrawTexturePro(board1, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    dest = { 490.f, 120.f, 1138.f / 4.f, 397.f / 4.f };
    DrawTexturePro(board1, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    source = { 0, 0, (float)board2.width, (float)board2.height };
    dest = { 440.f, 20.f, 1571.f / 4.f, 421.f / 4.f };
    DrawTexturePro(board2, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    //Draw heart
    source = { 0, 0, (float)heartTexture.width, (float)heartTexture.height };
    dest = { 55.f, 45.f, 40.f, 40.f };
    DrawTexturePro(heartTexture, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    DrawText(to_string(player->getLives()).c_str(), 130, 45, 40, BLACK);
    //

    //Draw Coin
    source = { 0, 0, (float)coinTexture.width, (float)coinTexture.height };
    dest = { 55.f, 145.f, 40.f, 40.f };
    DrawTexturePro(coinTexture, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    DrawText(to_string(player->getCoins()).c_str(), 130, 145, 40, BLACK);
    //

    //Draw X sign
    source = { 0, 0, (float)multiplicationSign.width, (float)multiplicationSign.height };
    dest = { 100.f, 55.f, 20.f, 20.f };
    DrawTexturePro(multiplicationSign, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    dest = { 100.f, 155.f, 20.f, 20.f };
    DrawTexturePro(multiplicationSign, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    //

    DrawText(to_string(player->getScores()).c_str(), 440.f + 1571.f / 8.f - MeasureTextEx(GetFontDefault(), to_string(player->getScores()).c_str(), 45.f, 0.f).x / 2.f, 45, 45, BLACK);

    DrawText(globalGameEngine->getCurrentMapName().c_str(), 530, 145, 45, BLACK);
    int timer = floor((globalGameEngine->getRemainingTime()));
    DrawText(to_string(timer).c_str(), 480.f + 1571.f / 8.f - MeasureTextEx(GetFontDefault(), to_string(timer).c_str(), 45.f, 0.f).x / 2.f, 145, 45, BLACK);


    // draw Home, restart, sound_on/off
    source = { 0.f, 0.f, (float)home.width, (float)home.height };
    dest = {(float)GetScreenWidth() - 100, 100.f, 50.f, 50.f};
    DrawTexturePro(home, source, dest, { 0.f, 0.f }, 0.f, WHITE);
}

void GUI::drawPauseMenu()
{
    Rectangle dest, source;
    source = { 2043.f, 295.f, 1997.f, 1465.f };
    dest = { 300.f, 200.f, 1997.f / 3.f, 1465.f / 3.f };
    DrawTexturePro(board, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    DrawText("PAUSED", 460, 370, 90, BLACK);
}

void GUI::drawLevelClear()
{
    Rectangle dest, source;
    source = { 2043.f, 295.f, 1997.f, 1465.f };
    dest = { 300.f, 200.f, 1997.f / 3.f, 1465.f / 3.f };
    DrawTexturePro(board, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    DrawText("CLEARED", 440, 370, 90, BLACK);
    DrawText("Press Enter to continue", 360, 550, 45, BLACK);
}

void GUI::drawDeathScreen()
{
    const char* text = "YOU DIED";
    int fontSize = 90;
    int screenWidth = 1280;
    int screenHeight = 800;

    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize;

    int posX = (screenWidth - textWidth) / 2;
    int posY = (screenHeight - textHeight) / 2;

    DrawText(text, posX, posY, fontSize, RED);
}

void GUI::drawGameOverScreen()
{
    Rectangle dest, source;
    source = { 2043.f, 295.f, 1997.f, 1465.f };
    dest = { 300.f, 200.f, 1997.f / 3.f, 1465.f / 3.f };
    DrawTexturePro(board, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    DrawText("Game Over", 420, 370, 90, BLACK);
    DrawText("Press Enter to continue", 360, 550, 45, BLACK);
}
