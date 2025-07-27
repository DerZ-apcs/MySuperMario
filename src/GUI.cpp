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

bool GUI::home_is_pressed = false;
bool GUI::restart_is_pressed = false;
bool GUI::sound_is_pressed = false;
bool GUI::setting_is_pressed = false;

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
    // Scores
    DrawText(to_string(player->getScores()).c_str(), 440.f + 1571.f / 8.f - MeasureTextEx(GetFontDefault(), to_string(player->getScores()).c_str(), 45.f, 0.f).x / 2.f, 45, 45, BLACK);

    DrawText(globalGameEngine->getCurrentMapName().c_str(), 530, 145, 45, BLACK);
    int timer = floor((globalGameEngine->getRemainingTime()));
    DrawText(to_string(timer).c_str(), 480.f + 1571.f / 8.f - MeasureTextEx(GetFontDefault(), to_string(timer).c_str(), 45.f, 0.f).x / 2.f, 145, 45, BLACK);

    // draw setting button
    source = { 0, 0, (float)setting.width, (float)restart.height };
    dest = { (float)GetScreenWidth() - 100, 30.f, 80.f, 80.f };
    DrawTexturePro(setting, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    setting_is_pressed = CheckCollisionPointRec(GetMousePosition(), dest) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void GUI::drawStatusBar(std::vector<std::unique_ptr<Character>>& multiplayers)
{
    Rectangle dest, source;
	if (multiplayers.empty()) return;
    //Draw board
    dest = { 20.f, 20.f, 1138.f / 4.f, 397.f / 4.f };
    source = { 0, 0, (float)board1.width, (float)board1.height };
    DrawTexturePro(board1, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    dest = { 20.f, 120.f, 1138.f / 4.f, 397.f / 4.f };
    DrawTexturePro(board1, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    source = { 0, 0, (float)board2.width, (float)board2.height };
    dest = { 320.f, 20.f, 1571.f / 4.f, 421.f / 4.f };
    DrawTexturePro(board2, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    //Draw heart
    source = { 0, 0, (float)heartTexture.width, (float)heartTexture.height };
    dest = { 55.f, 45.f, 40.f, 40.f };
    DrawTexturePro(heartTexture, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    DrawText(to_string(multiplayers[0]->getLives()).c_str(), 130, 45, 40, BLACK);
     // player1
    std::string p1 = "P1";
    DrawText(p1.c_str(), 200, 45, 40, BLACK);

    //Draw Coin
    source = { 0, 0, (float)coinTexture.width, (float)coinTexture.height };
    dest = { 55.f, 145.f, 40.f, 40.f };
    DrawTexturePro(coinTexture, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    DrawText(to_string(multiplayers[0]->getCoins()).c_str(), 130, 145, 40, BLACK);
    //

    //Draw X sign
    source = { 0, 0, (float)multiplicationSign.width, (float)multiplicationSign.height };
    dest = { 100.f, 55.f, 20.f, 20.f };
    DrawTexturePro(multiplicationSign, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    dest = { 100.f, 155.f, 20.f, 20.f };
    DrawTexturePro(multiplicationSign, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    // Scores
    DrawText(to_string(multiplayers[0]->getScores()).c_str(), 320.f + 1571.f / 8.f - MeasureTextEx(GetFontDefault(), to_string(multiplayers[0]->getScores()).c_str(), 45.f, 0.f).x / 2.f, 45, 45, BLACK);

    // for player 2
    
        //Draw board
        dest = { 750.f, 20.f, 1138.f / 4.f, 397.f / 4.f };
        source = { 0, 0, (float)board1.width, (float)board1.height };
        DrawTexturePro(board1, source, dest, { 0.f, 0.f }, 0.f, WHITE);

        dest = { 750.f, 120.f, 1138.f / 4.f, 397.f / 4.f };
        DrawTexturePro(board1, source, dest, { 0.f, 0.f }, 0.f, WHITE);

        source = { 0, 0, (float)board2.width, (float)board2.height };
        dest = { 1040.f, 20.f, 1571.f / 4.f, 421.f / 4.f };
        DrawTexturePro(board2, source, dest, { 0.f, 0.f }, 0.f, WHITE);

        //Draw heart
        source = { 0, 0, (float)heartTexture.width, (float)heartTexture.height };
        dest = { 785.f, 45.f, 40.f, 40.f };
        DrawTexturePro(heartTexture, source, dest, { 0.f, 0.f }, 0.f, WHITE);
        DrawText(to_string(multiplayers[1]->getLives()).c_str(), 860, 45, 40, BLACK);
        //
        std::string p2 = "P2";
        DrawText(p2.c_str(), 930, 45, 40, BLACK);
        //Draw Coin
        source = { 0, 0, (float)coinTexture.width, (float)coinTexture.height };
        dest = { 785.f, 145.f, 40.f, 40.f };
        DrawTexturePro(coinTexture, source, dest, { 0.f, 0.f }, 0.f, WHITE);
        DrawText(to_string(multiplayers[1]->getCoins()).c_str(), 860, 145, 40, BLACK);
        //

        //Draw X sign
        source = { 0, 0, (float)multiplicationSign.width, (float)multiplicationSign.height };
        dest = { 830.f, 55.f, 20.f, 20.f };
        DrawTexturePro(multiplicationSign, source, dest, { 0.f, 0.f }, 0.f, WHITE);

        dest = { 830.f, 155.f, 20.f, 20.f };
        DrawTexturePro(multiplicationSign, source, dest, { 0.f, 0.f }, 0.f, WHITE);
        // Scores
        DrawText(to_string(multiplayers[1]->getScores()).c_str(), 1040.f + 1571.f / 8.f - MeasureTextEx(GetFontDefault(), to_string(multiplayers[1]->getScores()).c_str(), 45.f, 0.f).x / 2.f, 45, 45, BLACK);
    

    // Map & Time
    DrawText(globalGameEngine->getCurrentMapName().c_str(), 1440, 145, 40, BLACK);
    int timer = floor((globalGameEngine->getRemainingTime()));
    DrawText(to_string(timer).c_str(), 1400.f + 1571.f / 8.f - MeasureTextEx(GetFontDefault(), to_string(timer).c_str(), 45.f, 0.f).x / 2.f, 145, 40, BLACK);

    // draw setting button
    source = { 0, 0, (float)setting.width, (float)restart.height };
    dest = { (float)GetScreenWidth() - 100, 30.f, 80.f, 80.f };
    DrawTexturePro(setting, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    setting_is_pressed = CheckCollisionPointRec(GetMousePosition(), dest) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}



void GUI::drawPauseMenu()
{
    Rectangle source = { 0, 0, (float)largeBoard.width, (float)largeBoard.height};
    Rectangle dest = { (float)GetScreenWidth() / 4.f , (float)GetScreenHeight() * 0.125f, (float)GetScreenWidth() / 2.f, (float)GetScreenHeight() * 0.75f};
    DrawTexturePro(largeBoard, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    const char* text = "PAUSED";
    int fontSize = 90;
    int textWidth = MeasureText(text, fontSize);

    // Center the text inside the destination rectangle
    float textX = dest.x + (dest.width - textWidth) / 2;
    float textY = dest.y + 100;

    DrawText(text, textX, textY, fontSize, BLACK);

    text = "Press Enter to continue";
    fontSize = 45;
    textWidth = MeasureText(text, fontSize);
    textX = dest.x + (dest.width - textWidth) / 2;
    textY = dest.y + 400;
    DrawText(text, textX, textY, fontSize, BLACK);

    // restart
    source = { 0, 0, (float)restart.width, (float)restart.height };
    dest = { textX + 100, textY - 170, 90, 90 };
    DrawTexturePro(restart, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    restart_is_pressed = CheckCollisionPointRec(GetMousePosition(), dest) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_R);

    // sound_on
    Texture2D sound = (SETTING.isMusicEnabled()) ? sound_on : sound_off;
    source = { 0, 0, (float)sound.width, (float)sound.height };
    dest = { textX + 350, textY - 170, 90, 90 };
    DrawTexturePro(sound, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    sound_is_pressed = CheckCollisionPointRec(GetMousePosition(), dest) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_V);

    // home
    source = { 0, 0, (float)home.width, (float)home.height };
    dest = { textX + 225, textY - 170, 90, 90 };
    DrawTexturePro(home, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    home_is_pressed = CheckCollisionPointRec(GetMousePosition(), dest) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_H);

}

void GUI::drawLevelClear()
{
    Rectangle source = { 0, 0, (float)largeBoard.width, (float)largeBoard.height };
    Rectangle dest = { (float)GetScreenWidth() / 4.f , (float)GetScreenHeight() * 0.125f, (float)GetScreenWidth() / 2.f, (float)GetScreenHeight() * 0.75f };
    DrawTexturePro(largeBoard, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    const char* text = "CLEARED";
    int fontSize = 90;
    int textWidth = MeasureText(text, fontSize);

    // Center the text inside the destination rectangle
    float textX = dest.x + (dest.width - textWidth) / 2;
    float textY = dest.y + 100;

    DrawText(text, textX, textY, fontSize, BLACK);

    text = "Press Enter to continue";
    fontSize = 45;
    textWidth = MeasureText(text, fontSize);
    textX = dest.x + (dest.width - textWidth) / 2;
    textY = dest.y + 400;
    DrawText(text, textX, textY, fontSize, BLACK);
}

void GUI::drawDeathScreen()
{
    const char* text = "YOU DIED";
    int fontSize = 90;

    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize;

    int posX = ((float)GetScreenWidth() - textWidth) / 2;
    int posY = ((float)GetScreenHeight() - textHeight) / 2 - 200;

    DrawText(text, posX, posY, fontSize, RED);

    text = "Press Enter to continue";
    fontSize = 45;
    textWidth = MeasureText(text, fontSize);
    float textX = ((float)GetScreenWidth() - textWidth) / 2;
    float textY = posY + 200;
    DrawText(text, textX, textY, fontSize, BLACK);
}

void GUI::drawGameOverScreen()
{
    Rectangle source = { 0, 0, (float)largeBoard.width, (float)largeBoard.height };
    Rectangle dest = { (float)GetScreenWidth() / 4.f , (float)GetScreenHeight() * 0.125f, (float)GetScreenWidth() / 2.f, (float)GetScreenHeight() * 0.75f };
    DrawTexturePro(largeBoard, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    const char* text = "GAME OVER";
    int fontSize = 90;
    int textWidth = MeasureText(text, fontSize);

    // Center the text inside the destination rectangle
    float textX = dest.x + (dest.width - textWidth) / 2;
    float textY = dest.y + 100;

    DrawText(text, textX, textY, fontSize, BLACK);

    text = "Press Enter to continue";
    fontSize = 45;
    textWidth = MeasureText(text, fontSize);
    textX = dest.x + (dest.width - textWidth) / 2;
    textY = dest.y + 400;
    DrawText(text, textX, textY, fontSize, BLACK);
}
