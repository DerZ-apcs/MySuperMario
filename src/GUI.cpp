#include "../include/GUI.h"
#include"../include/Character.h"
#include "../include/GameEngine.h"
#include <TextButton.h>

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
Texture2D GUI::choosingArrow;
// for hud
Texture2D GUI::guiTime;
Texture2D GUI::guiNextitem;
Texture2D GUI::guiCoin;
Texture2D GUI::guiClock;
Texture2D GUI::guiCourseClear;
Texture2D GUI::gui1Up;
Texture2D GUI::gui3Up;
Texture2D GUI::guiTimeUp;
Texture2D GUI::guiLuigiStart;
Texture2D GUI::guiMarioStart;
Texture2D GUI::guiX;
Texture2D GUI::guiMario;
Texture2D GUI::guiLuigi;

bool GUI::home_is_pressed = false;
bool GUI::restart_is_pressed = false;
bool GUI::sound_is_pressed = false;
bool GUI::setting_is_pressed = false;

void GUI::drawPlayerStatus(const Character* player, Vector2 origin) {
    float scale = 0.75f;

    if (player->getCharacterType() == CharacterType::MARIO) {
        DrawTexturePro(guiMario, { 0, 0, (float)guiMario.width, (float)guiMario.height },
            { origin.x, origin.y, 160 * scale, 32 * scale }, { 0, 0 }, 0.f, WHITE);
    }
    else if (player->getCharacterType() == CharacterType::LUIGI) {
        DrawTexturePro(guiLuigi, { 0, 0, (float)guiLuigi.width, (float)guiLuigi.height },
            { origin.x, origin.y, 160 * scale, 32 * scale }, { 0, 0 }, 0.f, WHITE);
    }
    else if (player->getCharacterType() == TOAD) {
		Font* font = RESOURCE_MANAGER.getFont("SMW");
		TextButton::DrawTextWithOutline(font, "TOAD", { origin.x, origin.y }, 32 * scale, 5, BLUE, BLACK);
    }
    else if (player->getCharacterType() == PEACH) {
        Font* font = RESOURCE_MANAGER.getFont("SMW");
        TextButton::DrawTextWithOutline(font, "PEACH", { origin.x, origin.y }, 32 * scale, 5, PINK, BLACK);
    }
	else if (player->getCharacterType() == MARISA) {
        Font* font = RESOURCE_MANAGER.getFont("SMW");
        TextButton::DrawTextWithOutline(font, "MARISA", { origin.x, origin.y }, 32 * scale, 5, BROWN, BLACK);

	}

    if (!guiX.id) guiX = RESOURCE_MANAGER.getTexture("guiX");

    // Lives
    DrawTexturePro(guiX, { 0, 0, (float)guiX.width, (float)guiX.height },
        { origin.x + 20, origin.y + 40, 28 * scale, 28 * scale }, { 0, 0 }, 0.f, WHITE);
    drawSmallNumber(player->getLives(), { origin.x + 50, origin.y + 40 }, 20.f);

    // Next item
    if (!guiNextitem.id) guiNextitem = RESOURCE_MANAGER.getTexture("guiNextItem");
    DrawTexturePro(guiNextitem, { 0, 0, (float)guiNextitem.width, (float)guiNextitem.height },
        { origin.x + 150, origin.y, 112 * scale, 112 * scale }, { 0, 0 }, 0.f, WHITE);

    // Coins
    if (!guiCoin.id) guiCoin = RESOURCE_MANAGER.getTexture("guiCoin");
    DrawTexturePro(guiCoin, { 0, 0, (float)guiCoin.width, (float)guiCoin.height },
        { origin.x + 280, origin.y, 32 * scale, 32 * scale }, { 0, 0 }, 0.f, WHITE);
    DrawTexturePro(guiX, { 0, 0, (float)guiX.width, (float)guiX.height },
        { origin.x + 315, origin.y, 28 * scale, 28 * scale }, { 0, 0 }, 0.f, WHITE);
    drawSmallNumber(player->getCoins(), { origin.x + 360.f, origin.y }, 20.f);

    // Score
    drawSmallNumber(player->getScores(), { origin.x + 280.f, origin.y + 40.f }, 20.f);
}

void GUI::drawStatusBar(const Character* player) {
    //Rectangle dest, source;

    // draw lives
	if (player->getCharacterType() == CharacterType::MARIO) {
        DrawTexturePro(guiMario, { 0, 0, (float)guiMario.width, (float)guiMario.height }, {400, 40, 160 * 0.75, 32 * 0.75 }, {0, 0}, 0.f, WHITE);
	}
	else if (player->getCharacterType() == CharacterType::LUIGI) {
        DrawTexturePro(guiLuigi, { 0, 0, (float)guiLuigi.width, (float)guiLuigi.height }, { 400, 40, 160 * 0.75, 32 * 0.75 }, { 0, 0 }, 0.f, WHITE);
	}
    else if (player->getCharacterType() == TOAD) {
        Font* font = RESOURCE_MANAGER.getFont("SMW");
        TextButton::DrawTextWithOutline(font, "TOAD", { 400, 40 }, 160 * 0.75, 5, BLUE, BLACK);
    }
    else if (player->getCharacterType() == PEACH) {
        Font* font = RESOURCE_MANAGER.getFont("SMW");
        TextButton::DrawTextWithOutline(font, "PEACH", { 400, 40 }, 160 * 0.75, 5, PINK, BLACK);
    }
    else if (player->getCharacterType() == MARISA) {
        Font* font = RESOURCE_MANAGER.getFont("SMW");
        TextButton::DrawTextWithOutline(font, "MARISA", { 400, 40 }, 160 * 0.75, 5, BROWN, BLACK);
    }

	if (!guiX.id) {
		guiX = RESOURCE_MANAGER.getTexture("guiX");
	}
    DrawTexturePro(guiX, { 0, 0, (float)guiX.width, (float)guiX.height }, { 420, 80, 28 * 0.75, 28 * 0.75 }, { 0, 0 }, 0.f, WHITE);
	drawSmallNumber(player->getLives(), { 450.f, 80.f }, 20.f);

    // draw next item
	//drawNumber(player->getNextItem(), { 300.f, 30.f }, 20.f);
	if (!guiNextitem.id) {
		guiNextitem = RESOURCE_MANAGER.getTexture("guiNextItem");
	}
    DrawTexturePro(guiNextitem, { 0, 0, (float)guiNextitem.width, (float)guiNextitem.height }, { 744, 20, 112 * 0.75, 112 * 0.75 }, { 0, 0 }, 0.f, WHITE);

    // draw time
	if (!guiTime.id) {
		guiTime = RESOURCE_MANAGER.getTexture("guiTime");
	}
    DrawTexturePro(guiTime, { 0, 0, (float)guiTime.width, (float)guiTime.height }, { 1000, 40, 48 * 2 * 0.75, 28 * 0.75 }, { 0, 0 }, 0.f, WHITE);
	int timer = floor(globalGameEngine->getRemainingTime());
	drawYellowNumber(timer, { 1005.f, 80.f }, 20.f);

    //Draw Coin
	if (!guiCoin.id) {
		guiCoin = RESOURCE_MANAGER.getTexture("guiCoin");
	}
    DrawTexturePro(guiCoin, { 0, 0, (float)guiCoin.width, (float)guiCoin.height }, { 1200, 40, 32 * 0.75, 32 * 0.75 }, { 0, 0 }, 0.f, WHITE);
    DrawTexturePro(guiX, { 0, 0, (float)guiX.width, (float)guiX.height }, { 1235, 40, 28 * 0.75, 28 * 0.75 }, { 0, 0 }, 0.f, WHITE);
	drawSmallNumber(player->getCoins(), { 1300.f, 40.f }, 20.f);
	// draw score
	drawSmallNumber(player->getScores(), { 1200.f, 80.f }, 20.f);

    //// draw setting button
    //source = { 0, 0, (float)setting.width, (float)restart.height };
    //dest = { (float)GetScreenWidth() - 100, 30.f, 80.f, 80.f };
    //DrawTexturePro(setting, source, dest, { 0.f,
    // 0.f }, 0.f, WHITE);
    //setting_is_pressed = CheckCollisionPointRec(GetMousePosition(), dest) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void GUI::drawStatusBar(std::vector<std::unique_ptr<Character>>& multiplayers)
{
    const float spacing = 500.f;       // Distance between player GUIs
    const float startX = 50.f;         // Starting X position
    const float y = 40.f;              // Y position (same for all)

    for (size_t i = 0; i < multiplayers.size(); ++i)
    {
        Vector2 origin = { startX + i * spacing, y };
        drawPlayerStatus(multiplayers[i].get(), origin);
    }

    // Draw timer (center screen)
    if (!guiTime.id) guiTime = RESOURCE_MANAGER.getTexture("guiTime");

    DrawTexturePro(guiTime, { 0, 0, (float)guiTime.width, (float)guiTime.height },
        { GetScreenWidth() / 2.f + 400.f, y, 48 * 2 * 0.75f, 28 * 0.75f }, { 0, 0 }, 0.f, WHITE);

    int timer = floor(globalGameEngine->getRemainingTime());
    drawYellowNumber(timer, { GetScreenWidth() / 2.f + 405.f, y + 40.f }, 20.f);

    //// Draw setting button (top right)
    //Rectangle source = { 0, 0, (float)setting.width, (float)restart.height };
    //Rectangle dest = { (float)GetScreenWidth() - 100.f, 30.f, 80.f, 80.f };
    //DrawTexturePro(setting, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    //setting_is_pressed = CheckCollisionPointRec(GetMousePosition(), dest) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void GUI::drawPauseMenu()
{
    Rectangle source = { 0, 0, (float)largeBoard.width, (float)largeBoard.height};
    Rectangle dest = { (float)GetScreenWidth() / 4.f , (float)GetScreenHeight() * 0.125f, (float)GetScreenWidth() / 2.f, (float)GetScreenHeight() * 0.75f};
    DrawTexturePro(largeBoard, source, dest, { 0.f, 0.f }, 0.f, WHITE);

    const char* text = "PAUSED";
    int fontSize = 90;
	Font* font = RESOURCE_MANAGER.getFont("SMW");
    int textWidth = MeasureTextEx(*font ,text, fontSize, 0).x;

    // Center the text inside the destination rectangle
    float textX = dest.x + (dest.width - textWidth) / 2;
    float textY = dest.y + 100;

    DrawTextPro(*font, text, { textX, textY }, { 0, 0 }, 0.f, fontSize, 0.f, BLACK);

    text = "Press Enter to continue";
    fontSize = 45;
    textWidth = MeasureTextEx(*font, text, fontSize, 0).x;
    textX = dest.x + (dest.width - textWidth) / 2;
    textY = dest.y + 400;
    DrawTextPro(*font, text, { textX, textY }, { 0, 0 }, 0.f, fontSize, 0.f, BLACK);

    // restart
    source = { 0, 0, (float)restart.width, (float)restart.height };
    dest = { textX + 105, textY - 170, 90, 90 };
    DrawTexturePro(restart, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    restart_is_pressed = CheckCollisionPointRec(GetMousePosition(), dest) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_R);

    // sound_on
    Texture2D sound = (SETTING.isMusicEnabled()) ? sound_on : sound_off;
    source = { 0, 0, (float)sound.width, (float)sound.height };
    dest = { textX + 355, textY - 170, 90, 90 };
    DrawTexturePro(sound, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    sound_is_pressed = CheckCollisionPointRec(GetMousePosition(), dest) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_V);

    // home
    source = { 0, 0, (float)home.width, (float)home.height };
    dest = { textX + 230, textY - 170, 90, 90 };
    DrawTexturePro(home, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    home_is_pressed = CheckCollisionPointRec(GetMousePosition(), dest) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_H);
}

void GUI::drawLevelClear()
{
	//DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.3f));
	Texture2D courseClear = RESOURCE_MANAGER.getTexture("guiCourseClear");
    DrawTexturePro(courseClear, {0, 0, (float)courseClear.width, (float)courseClear.height}, {800 - 204, 400 - 26 - 150,204 * 2, 26 * 2}, {0, 0}, 0.f, WHITE);

    Font* customFont = RESOURCE_MANAGER.getFont("SMW");
    const char* text = "Press Enter to continue";
    int fontSize = 45;
    int textWidth = MeasureTextEx(*customFont, text, fontSize, 0).x;
    float textX = 800 - textWidth / 2.f; // Center the text horizontally
    float textY = 400;
    DrawTextPro(*customFont, text, { textX, textY }, { 0, 0 }, 0.f, fontSize, 0.f, BLACK);
}

void GUI::drawDeathScreen()
{
	//DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.3f));

    const char* text = "YOU DIED";
    int fontSize = 90;
    Font* customFont = RESOURCE_MANAGER.getFont("SMW");
    Vector2 textSize = MeasureTextEx(*customFont, text, fontSize, 0);
    int textWidth = textSize.x;
    int textHeight = textSize.y;
    int posX = ((float)GetScreenWidth() - textWidth) / 2;
    int posY = ((float)GetScreenHeight() - textHeight) / 2 - 150;
    DrawTextPro(*customFont, text, { (float)posX, (float)posY }, { 0, 0 }, 0.f, fontSize, 0.f, RED);

    text = "Press Enter to continue";
    fontSize = 45;
    textSize = MeasureTextEx(*customFont, text, fontSize, 0);
    textWidth = textSize.x;
    float textX = ((float)GetScreenWidth() - textWidth) / 2;
    float textY = 400;
    DrawTextPro(*customFont, text, { textX, textY }, { 0, 0 }, 0.f, fontSize, 0.f, BLACK);
}

void GUI::drawGameOverScreen()
{
	//DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
	Texture2D gameover = RESOURCE_MANAGER.getTexture("guiGameOver");
    DrawTexturePro(gameover, { 0, 0, (float)gameover.width, (float)gameover.height }, { 800 - 160, 400 - 32 - 150,160 * 2, 32 * 2 }, { 0, 0 }, 0.f, WHITE);

	Font* font = RESOURCE_MANAGER.getFont("SMW");
    const char* text = "Press Enter to continue";
    int fontSize = 45;
    int textWidth = MeasureTextEx(*font, text, fontSize, 0).x;
    float textX = ((float)GetScreenWidth() - textWidth) / 2;
    float textY = 400;
    DrawTextPro(*font, text, { textX, textY }, { 0, 0 }, 0.f, fontSize, 0.f, BLACK);
}

void GUI::drawNumber(int number, Vector2 position, float spacing)
{
    std::string numStr = std::to_string(number);
    for (size_t i = 0; i < numStr.length(); ++i) {
        int digit = numStr[i] - '0';
        Texture2D tex = RESOURCE_MANAGER.digitTextures[digit];
        DrawTextureEx(tex, {position.x + i * spacing, position.y }, 0.f, 1.5f, WHITE);
    }
}


void GUI::drawSmallNumber(int number, Vector2 position, float spacing)
{
    std::string numStr = std::to_string(number);
    for (size_t i = 0; i < numStr.length(); ++i) {
        int digit = numStr[i] - '0';
        Texture2D tex = RESOURCE_MANAGER.smallDigitTextures[digit];
        DrawTextureEx(tex, { position.x + i * spacing, position.y }, 0.f, 1.5f, WHITE);
    }
}

void GUI::drawYellowNumber(int number, Vector2 position, float spacing)
{
    std::string numStr = std::to_string(number);
    for (size_t i = 0; i < numStr.length(); ++i) {
        int digit = numStr[i] - '0';
        Texture2D tex = RESOURCE_MANAGER.yellowDigitTextures[digit];
        DrawTextureEx(tex, { position.x + i * spacing, position.y }, 0.f, 1.5f, WHITE);
    }
}
