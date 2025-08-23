#include "../include/GUI.h"
#include "../include/Level.h"
#include "../include/Character.h"
#include "../include/GameEngine.h"
#include <TextButton.h>
#include "../include/Boss.h"
#include "../include/EditorEngine.h"

Texture2D GUI::heartTexture;
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

// for choosing character
Texture2D GUI::ChoosingMario;
Texture2D GUI::ChoosingLuigi;
Texture2D GUI::ChoosingPeach;
Texture2D GUI::ChoosingMarisa;
Texture2D GUI::ChoosingToad;
Texture2D GUI::GuiP1;
Texture2D GUI::GuiP2;
std::vector <Texture2D> GUI::choosingTextures;

bool GUI::inSelection = false;
bool GUI::return_is_pressed = false;
bool GUI::home_is_pressed = false;
bool GUI::restart_is_pressed = false;
bool GUI::sound_is_pressed = false;
bool GUI::setting_is_pressed = false;
bool GUI::input_box_is_active = false;
bool GUI::back_editor_is_pressed = false;

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
        TextButton::DrawTextWithOutline(font, "TOAD", { 400, 40 }, 160 * 0.2, 5, BLUE, BLACK);
    }
    else if (player->getCharacterType() == PEACH) {
        Font* font = RESOURCE_MANAGER.getFont("SMW");
        TextButton::DrawTextWithOutline(font, "PEACH", { 400, 40 }, 160 * 0.2, 5, PINK, BLACK);
    }
    else if (player->getCharacterType() == MARISA) {
        Font* font = RESOURCE_MANAGER.getFont("SMW");
        TextButton::DrawTextWithOutline(font, "MARISA", { 400, 40 }, 160 * 0.2, 5, BROWN, BLACK);
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

    text = "Press Space to continue";
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

    inSelection = inSelection || IsKeyPressed(KEY_C) || IsKeyPressed(KEY_F8);
}

void GUI::drawLevelClear()
{
	//DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.3f));
	Texture2D courseClear = RESOURCE_MANAGER.getTexture("guiCourseClear");
    DrawTexturePro(courseClear, {0, 0, (float)courseClear.width, (float)courseClear.height}, {800 - 204, 400 - 26 - 150,204 * 2, 26 * 2}, {0, 0}, 0.f, WHITE);

    Font* customFont = RESOURCE_MANAGER.getFont("SMW");
    const char* text = "Press Space to continue";
    int fontSize = 45;
    int textWidth = MeasureTextEx(*customFont, text, fontSize, 0).x;
    float textX = 800 - textWidth / 2.f; // Center the text horizontally
    float textY = 400;
    DrawTextPro(*customFont, text, { textX, textY }, { 0, 0 }, 0.f, fontSize, 0.f, BLACK);
}

void GUI::drawVictory() {

}
void GUI::drawTransitioningBetweenMap() {

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

    text = "Press Space to continue";
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
    const char* text = "Press Space to continue";
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

void GUI::drawEditorUI() {
    DrawRectangle(0, 0, 468, GetScreenHeight(), Fade(LIGHTGRAY, 0.8f)); // sidebar
    DrawText("Editor Menu", 20, 20, 30, BLACK);

    DrawText(TextFormat("Grid: %d x %d", globalEditorEngine->getWidth(), 30), 20, 60, 20, DARKGRAY);
    Color Normal = DARKGRAY;
	Color hovered = LIGHTGRAY;
	Color TextNormal = WHITE;
	Color TextHovered = BLACK;

	Rectangle saveButton = { 20, 100, 100, 30 };
	if (CheckCollisionPointRec(GetMousePosition(), saveButton)) {
        DrawRectangleRec(saveButton, hovered);
        DrawText("Save", 30, 108, 16, TextHovered);
    }
    else {
		DrawRectangleRec(saveButton, Normal);
		DrawText("Save", 30, 108, 16, TextNormal);
    }


	Rectangle loadButton = { 140, 100, 100, 30 };
    if (CheckCollisionPointRec(GetMousePosition(), loadButton)) {
        DrawRectangleRec(loadButton, hovered);
        DrawText("Load", 150, 108, 16, TextHovered);
    }
    else {
        DrawRectangleRec(loadButton, Normal);
        DrawText("Load", 150, 108, 16, TextNormal);
    }

	static bool isResizing = false;
	Rectangle resizeButton = { 310, 100, 100, 30 };
	if (CheckCollisionPointRec(GetMousePosition(), resizeButton)) {
		DrawRectangleRec(resizeButton, hovered);
		DrawText("Resize", 320, 108, 16, TextHovered);
	}
	else {
		DrawRectangleRec(resizeButton, Normal);
		DrawText("Resize", 320, 108, 16, TextNormal);
	}

	Rectangle playButton = { 20, 140, 100, 30 };
	if (CheckCollisionPointRec(GetMousePosition(), playButton)) {
		DrawRectangleRec(playButton, hovered);
		DrawText("Play", 30, 148, 16, TextHovered);
	}
	else {
		DrawRectangleRec(playButton, Normal);
		DrawText("Play", 30, 148, 16, TextNormal);
	}

    // Draw back button
    Rectangle backButton = { 140, 140, 100, 30 };
	if (CheckCollisionPointRec(GetMousePosition(), backButton)) {
		DrawRectangleRec(backButton, hovered);
		DrawText("Back", 150, 148, 16, TextHovered);
	}
	else {
		DrawRectangleRec(backButton, Normal);
		DrawText("Back", 150, 148, 16, TextNormal);
	}

    static int slot = 1;
    drawMapChoice(slot);


	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), backButton)) {
		back_editor_is_pressed = true;
	}

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), saveButton)) {
        globalEditorEngine->saveToJson(slot);
        printf("Map %d saved successfully!\n", slot);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), loadButton)) {
        globalEditorEngine->loadFromJson(slot);
        printf("Map %d loaded successfully!\n", slot);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), resizeButton)) { 
        isResizing = true; 
		input_box_is_active = true;
    }
    if (isResizing) {
		static std::string inputText = "100"; 
		Vector2 inputBoxPos = { 310, 140 };
        drawInputBox(inputBoxPos, inputText);
        if (input_box_is_active == false) {
            int newWidth = std::stoi(inputText);
            if (newWidth > 0) {
                globalEditorEngine->resizeGrid(newWidth);
                isResizing = false;
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), playButton)) {
        globalEditorEngine->loadFromJson(slot);

        if (globalGameEngine != nullptr) {
            delete globalGameEngine;
            globalGameEngine = nullptr;
        }

        std::string filename = "resources/maps/emap_" + std::to_string(slot) + ".json";
        Level* level = make_unique<Level>(filename, "BACKGROUND_1", "MUSIC_1", "2 - 1").release();
        std::vector<std::unique_ptr<Character>> character;
        character.push_back(std::make_unique<Mario>());
        character[0]->setPosition({ 20, 200 });
        character[0]->setVel({ 0, 0 });
        character[0]->setState(FALLING);
        globalGameEngine = new GameEngine(1600, 800, *level, &character);
        globalGameEngine->loadGameMap(*level);
		printf("Map loaded successfully!\n");

        while (globalGameEngine != nullptr) {
            if (globalGameEngine->run()) { break; }
            else { break; }
        }
        delete globalGameEngine;
        globalGameEngine = nullptr;
    }

	int displayMode = globalEditorEngine->getDisplayMode();
	Rectangle modeButton = { 20, 700, 100, 30 };
    if (displayMode == 0) {
		if (CheckCollisionPointRec(GetMousePosition(), modeButton)) {
			DrawRectangleRec(modeButton, hovered);
			DrawText("Blocks", 30, 708, 16, TextHovered);
		}
        else {
            DrawRectangleRec(modeButton, Normal);
            DrawText("Enemies", 30, 708, 16, TextNormal);
        }
    } else {
		if (CheckCollisionPointRec(GetMousePosition(), modeButton)) {
			DrawRectangleRec(modeButton, hovered);
			DrawText("Enemies", 30, 708, 16, TextHovered);
		}
        else {
            DrawRectangleRec(modeButton, Normal);
            DrawText("Blocks", 30, 708, 16, TextNormal);
        }
	}
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), modeButton)) {
        globalEditorEngine->setDisplayMode(1 - displayMode); // Toggle between 0 and 1
	}

    if (displayMode == 0) {
        std::vector<TileSelector> tiles = globalEditorEngine->getTiles();
        int selectedBlockId = globalEditorEngine->getSelectedBlockId();

        for (const auto& tile : tiles) {
            DrawTexture(RESOURCE_MANAGER.getTexture("TILE_" + std::to_string(tile.id)), tile.rect.x, tile.rect.y, WHITE);
            if (tile.id == selectedBlockId) {
                DrawRectangleLinesEx(tile.rect, 2, RED); // Highlight selected tile
            }
        }
    }
    else if (displayMode == 1) {
        std::vector<EnemySelector> enemies = globalEditorEngine->getEnemy();
        std::string selectedEnemyName = globalEditorEngine->getSelectedEnemyName();

        for (const auto& enemy : enemies) {
            DrawTexture(enemy.tex, enemy.rect.x, enemy.rect.y, WHITE);
            if (enemy.name == selectedEnemyName) {
                DrawRectangleLinesEx(enemy.rect, 2, RED); // Highlight selected enemy
            }
        }
    }
}

void GUI::drawItemChoice(Vector2 position, ITEM_TYPE& itemChoice) {
    // Draw item choice menu
    DrawRectangle(position.x, position.y, 200, 150, Fade(LIGHTGRAY, 0.8f));
    DrawText("Select Item:", position.x + 10, position.y + 10, 20, BLACK);
    int currentitem = 0;
    const char* items[] = { "Mushroom", "Flower", "Star", "Moon" };
    for (int i = 0; i < 4; i++) {
        DrawText(items[i], position.x + 10, position.y + 40 + i * 30, 20, BLACK);
		// Draw selection rectangle
        if (CheckCollisionPointRec(GetMousePosition(), { position.x + 10, position.y + 40 + i * 30, 180, 30 })) {
            DrawRectangleLines(position.x + 10, position.y + 40 + i * 30, 180, 30, BLUE);
		}   
        // use arrow up and down
		if (IsKeyPressed(KEY_UP) && currentitem > 0) {
			currentitem--;
		}
        if (IsKeyPressed(KEY_DOWN) && currentitem < 3) {
            currentitem++;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), { position.x + 10, position.y + 40 + i * 30, 180, 30 })) {
           switch (i) {
                case 0: itemChoice = MUSHROOM; break;
                case 1: itemChoice = FLOWER; break;
                case 2: itemChoice = STAR; break;
                case 3: itemChoice = MOON; break;
            }
        }
    }
}

void GUI::drawInputBox(Vector2 position, std::string& inputText)     {

    DrawRectangle(position.x, position.y, 100, 30, WHITE);    
    DrawText(inputText.c_str(), position.x + 10, position.y + 8, 20, BLACK);
    
    if (IsKeyPressed(KEY_BACKSPACE) && !inputText.empty()) {
        inputText.pop_back(); 
    } else if (IsKeyPressed(KEY_ENTER)) {
		input_box_is_active = false; 
        printf("Input confirmed: %s\n", inputText.c_str());
    } else {
        int key = GetCharPressed();
        while (key > 0) {
            if (inputText.length() < 8) {
                inputText += (char)key;
            }
            key = GetCharPressed();
        }
    }
}

void GUI::drawMapChoice(int& mapChoice) {
    const char* labels[3] = { "Map 1", "Map 2", "Map 3" };
    Rectangle buttons[3] = {
        { 20, 190, 100, 30 },
        { 140, 190, 100, 30 },
        { 260, 190, 100, 30 }
    };

    // Draw buttons
    for (int i = 0; i < 3; i++) {
		if (CheckCollisionPointRec(GetMousePosition(), buttons[i])) {
			DrawRectangleRec(buttons[i], LIGHTGRAY);
            DrawText(labels[i], (int)buttons[i].x + 10, (int)buttons[i].y + 8, 16, BLACK);
		}
		else {
			DrawRectangleRec(buttons[i], DARKGRAY);
            DrawText(labels[i], (int)buttons[i].x + 10, (int)buttons[i].y + 8, 16, WHITE);
		}

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), buttons[i])) {
            mapChoice = i + 1;  // slot 1, 2, or 3
        }

        if (i + 1 == mapChoice) {
            DrawRectangleLinesEx(buttons[i], 3, RED);
        }
    }
}

void GUI::drawBossHealthBar(const Boss* boss) {
    // Nếu không có boss (con trỏ là nullptr) hoặc boss đã chết, không vẽ gì cả
    if (!boss || boss->getCurrentHp() <= 0) {
        return;
    }
    if (!guiX.id) guiX = RESOURCE_MANAGER.getTexture("guiX");
    // Lives
	DrawTexturePro(heartTexture, { 0, 0, (float)heartTexture.width, (float)heartTexture.height },
		{ boss->getX(), boss->getY() - 45, 28, 28}, { 0, 0 }, 0.f, WHITE);

    DrawTexturePro(guiX, { 0, 0, (float)guiX.width, (float)guiX.height },
        { boss->getX() + boss->getWidth() / 2, boss->getY() - 40, 28 * 0.75, 28 * 0.75}, {0, 0}, 0.f, WHITE);
    drawSmallNumber(boss->getCurrentHp(), { boss->getX() + boss->getWidth() / 2 + 30, boss->getY() - 40}, 20.f);
}

void GUI::drawChoosingSingleCharacter(int& choice) {
	if (!inSelection) return; // Only draw if in selection mode
    // Background
    Texture2D selectionBg = RESOURCE_MANAGER.getTexture("SelectionBackground");
    DrawTexturePro(selectionBg, { 0, 0, (float)selectionBg.width, (float)selectionBg.height },
        { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, { 0, 0 }, 0.f, WHITE);
    // Draw Text    
    TextButton::DrawTextWithOutline(RESOURCE_MANAGER.getFont("SMW"), "Change Your Character", { 540, 200 }, 30.f, 5, WHITE, BLACK);
	TextButton::DrawTextWithOutline(RESOURCE_MANAGER.getFont("SMW"), "Press A/D to change", { 550, 250 }, 30.f, 5, WHITE, BLACK);

    // Draw character textures (Mario, Luigi, Toad, Peach, Marisa)
    DrawTexturePro(choosingTextures[0], { 0, 0, (float)choosingTextures[0].width, (float)choosingTextures[0].height },
        { 270, 500 - 24, 32 * 4, 46 * 4 }, { 0, 0 }, 0.f, WHITE); // Mario
    DrawTexturePro(choosingTextures[1], { 0, 0, (float)choosingTextures[1].width, (float)choosingTextures[1].height },
        { 270 + 1 * 225, 500 - 40, 32 * 4, 50 * 4 }, { 0, 0 }, 0.f, WHITE); // Luigi
    DrawTexturePro(choosingTextures[2], { 0, 0, (float)choosingTextures[2].width, (float)choosingTextures[2].height },
        { 270 + 2 * 225, 500, 32 * 4, 40 * 4 }, { 0, 0 }, 0.f, WHITE); // Toad
    DrawTexturePro(choosingTextures[3], { 0, 0, (float)choosingTextures[3].width, (float)choosingTextures[3].height },
        { 270 + 3 * 225, 500 - 32, 32 * 4, 48 * 4 }, { 0, 0 }, 0.f, WHITE); // Peach
    DrawTexturePro(choosingTextures[4], { 0, 0, (float)choosingTextures[4].width, (float)choosingTextures[4].height },
        { 270 + 4 * 225, 500, 32 * 4, 40 * 4 }, { 0, 0 }, 0.f, WHITE); // Marisa

    // Handle input for player (A/D to cycle through characters)
    if (IsKeyPressed(KEY_A)) {
        choice--;
        if (choice < 0) choice = 4;
    }
    else if (IsKeyPressed(KEY_D)) {
        choice++;
        if (choice > 4) choice = 0;
    }
    // Draw player indicator (GuiP1)
    DrawTexturePro(GuiP1, { 0, 0, (float)GuiP1.width, (float)GuiP1.height },
        { (float)280 + choice * 225 + 10, 350, 75, 105 }, { 0, 0 }, 0.f, WHITE);

    // Handle Enter key to confirm selection
    if (IsKeyPressed(KEY_ENTER)) {
        static Mario defaultCharacter; // Fallback if no existing 

        // Helper function to create and clone character based on choice
        auto createCharacter = [](int choice) -> std::unique_ptr<Character> {
            CharacterType type;
            switch (choice) {
            case 0: type = MARIO; break;
            case 1: type = LUIGI; break;
            case 2: type = TOAD; break;
            case 3: type = PEACH; break;
            case 4: type = MARISA; break;
            default: type = MARIO; // Fallback
            }

            // Create new character instance
            std::unique_ptr<Character> newCharacter;
            switch (type) {
            case MARIO: newCharacter = std::make_unique<Mario>(); break;
            case LUIGI: newCharacter = std::make_unique<Luigi>(); break;
            case TOAD: newCharacter = std::make_unique<Toad>(); break;
            case PEACH: newCharacter = std::make_unique<Peach>(); break;
            case MARISA: newCharacter = std::make_unique<Marisa>(); break;
            default: newCharacter = std::make_unique<Mario>(); // Fallback
            }
            newCharacter->clone(defaultCharacter, type);
            return newCharacter;
            };

		auto newCharacter = createCharacter(choice);
        newCharacter->setPosition(globalGameEngine->getMultiplayers()[0]->getPosition());
        newCharacter->setVel(globalGameEngine->getMultiplayers()[0]->getVelocity());
        newCharacter->setState(globalGameEngine->getMultiplayers()[0]->getState());
        newCharacter->setLives(globalGameEngine->getMultiplayers()[0]->getLives());
        newCharacter->setScores(globalGameEngine->getMultiplayers()[0]->getScores());
        newCharacter->setCoins(globalGameEngine->getMultiplayers()[0]->getCoins());
		newCharacter->setCharacterState(globalGameEngine->getMultiplayers()[0]->getCharacterState());
        //delete old character
		globalGameEngine->getMultiplayers().clear(); // Clear existing players
        // Create and add player
        globalGameEngine->getMultiplayers().push_back(std::move(newCharacter));
        // Set player ID
        if (!globalGameEngine->getMultiplayers().empty()) {
            globalGameEngine->getMultiplayers()[0]->setPlayerid(0);
        }

        return_is_pressed = true; // Indicate that the players have been chosen
        inSelection = false;
    }
}

void GUI::drawChoosingDualCharacter(int& choice1, int& choice2) {
    // Background
    if (!inSelection) return;
    Texture2D selectionBg = RESOURCE_MANAGER.getTexture("SelectionBackground");
    DrawTexturePro(selectionBg, { 0, 0, (float)selectionBg.width, (float)selectionBg.height },
        { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, { 0, 0 }, 0.f, WHITE);
    // Draw Text    
    TextButton::DrawTextWithOutline(RESOURCE_MANAGER.getFont("SMW"), "Change Your Character", { 540, 200 }, 30.f, 5, WHITE, BLACK);
    TextButton::DrawTextWithOutline(RESOURCE_MANAGER.getFont("SMW"), "Press A/D, arrow left/right to change", { 550, 250 }, 30.f, 5, WHITE, BLACK);

    // Draw character textures (Mario, Luigi, Toad, Peach, Marisa)
    DrawTexturePro(choosingTextures[0], { 0, 0, (float)choosingTextures[0].width, (float)choosingTextures[0].height },
        { 270, 500 - 24, 32 * 4, 46 * 4 }, { 0, 0 }, 0.f, WHITE); // Mario
    DrawTexturePro(choosingTextures[1], { 0, 0, (float)choosingTextures[1].width, (float)choosingTextures[1].height },
        { 270 + 1 * 225, 500 - 40, 32 * 4, 50 * 4 }, { 0, 0 }, 0.f, WHITE); // Luigi
    DrawTexturePro(choosingTextures[2], { 0, 0, (float)choosingTextures[2].width, (float)choosingTextures[2].height },
        { 270 + 2 * 225, 500, 32 * 4, 40 * 4 }, { 0, 0 }, 0.f, WHITE); // Toad
    DrawTexturePro(choosingTextures[3], { 0, 0, (float)choosingTextures[3].width, (float)choosingTextures[3].height },
        { 270 + 3 * 225, 500 - 32, 32 * 4, 48 * 4 }, { 0, 0 }, 0.f, WHITE); // Peach
    DrawTexturePro(choosingTextures[4], { 0, 0, (float)choosingTextures[4].width, (float)choosingTextures[4].height },
        { 270 + 4 * 225, 500, 32 * 4, 40 * 4 }, { 0, 0 }, 0.f, WHITE); // Marisa

    // Draw player indicators (GuiP1 and GuiP2)
    if (choice1 == choice2) {
        // Adjust positions to avoid overlap when both players select the same character
        DrawTexturePro(GuiP1, { 0, 0, (float)GuiP1.width, (float)GuiP1.height },
            { (float)280 + choice1 * 225 - 30, 350, 75, 105 }, { 0, 0 }, 0.f, WHITE);
        DrawTexturePro(GuiP2, { 0, 0, (float)GuiP2.width, (float)GuiP2.height },
            { (float)280 + choice2 * 225 + 55, 350, 75, 105 }, { 0, 0 }, 0.f, WHITE);
    }
    else {
        DrawTexturePro(GuiP1, { 0, 0, (float)GuiP1.width, (float)GuiP1.height },
            { (float)280 + choice1 * 225 + 10, 350, 75, 105 }, { 0, 0 }, 0.f, WHITE);
        DrawTexturePro(GuiP2, { 0, 0, (float)GuiP2.width, (float)GuiP2.height },
            { (float)280 + choice2 * 225 + 10, 350, 75, 105 }, { 0, 0 }, 0.f, WHITE);
    }

    // Handle input for player 1 (A/D to cycle through characters)
    if (IsKeyPressed(KEY_A)) {
        choice1--;
        if (choice1 < 0) choice1 = 4;
    }
    else if (IsKeyPressed(KEY_D)) {
        choice1++;
        if (choice1 > 4) choice1 = 0;
    }

    // Handle input for player 2 (Left/Right to cycle through characters)
    if (IsKeyPressed(KEY_LEFT)) {
        choice2--;
        if (choice2 < 0) choice2 = 4;
    }
    else if (IsKeyPressed(KEY_RIGHT)) {
        choice2++;
        if (choice2 > 4) choice2 = 0;
    }

    // Handle Enter key to confirm selections
    if (IsKeyPressed(KEY_ENTER)) {
        // Clear existing players
        static Mario templateCharacter;

        // Helper function to create character based on choice
        auto createCharacter = [](int choice) -> std::unique_ptr<Character> {
            CharacterType type;
            switch (choice) {
            case 0: type = MARIO; break;
            case 1: type = LUIGI;break;
            case 2: type = TOAD;break;
            case 3: type = PEACH;break;
            case 4: type = MARISA;break;
            default: type = MARIO; // Fallback
            }
            // Create new character instance
            std::unique_ptr<Character> newCharacter;
            switch (type) {
                case CharacterType::MARIO: newCharacter = std::make_unique<Mario>(); break;
                case CharacterType::LUIGI: newCharacter = std::make_unique<Luigi>(); break;
                case CharacterType::TOAD: newCharacter = std::make_unique<Toad>(); break;
                case CharacterType::PEACH: newCharacter = std::make_unique<Peach>(); break;
                case CharacterType::MARISA: newCharacter = std::make_unique<Marisa>(); break;
                default: newCharacter = std::make_unique<Mario>(); // Fallback
            }

            // Clone state from template character with specified characterType
            newCharacter->clone(templateCharacter, type);
            return newCharacter;
        };
        auto newCharacter1 = createCharacter(choice1);
        auto newCharacter2 = createCharacter(choice2);

        newCharacter1->setPosition(globalGameEngine->getMultiplayers()[0]->getPosition());
        newCharacter1->setVel(globalGameEngine->getMultiplayers()[0]->getVelocity());
        newCharacter1->setState(globalGameEngine->getMultiplayers()[0]->getState());
        newCharacter1->setLives(globalGameEngine->getMultiplayers()[0]->getLives());
        newCharacter1->setScores(globalGameEngine->getMultiplayers()[0]->getScores());
        newCharacter1->setCoins(globalGameEngine->getMultiplayers()[0]->getCoins());
        newCharacter1->setCharacterState(globalGameEngine->getMultiplayers()[0]->getCharacterState());
        // for player 2
        newCharacter2->setPosition(globalGameEngine->getMultiplayers()[1]->getPosition());
        newCharacter2->setVel(globalGameEngine->getMultiplayers()[1]->getVelocity());
        newCharacter2->setState(globalGameEngine->getMultiplayers()[1]->getState());
        newCharacter2->setLives(globalGameEngine->getMultiplayers()[1]->getLives());
        newCharacter2->setScores(globalGameEngine->getMultiplayers()[1]->getScores());
        newCharacter2->setCoins(globalGameEngine->getMultiplayers()[1]->getCoins());
        newCharacter2->setCharacterState(globalGameEngine->getMultiplayers()[1]->getCharacterState());
        
        globalGameEngine->getMultiplayers().clear();

        // Create and add player 1
        globalGameEngine->getMultiplayers().push_back(std::move(newCharacter1));
        // Create and add player 2
        globalGameEngine->getMultiplayers().push_back(std::move(newCharacter2));

        // Set player IDs
        if (!globalGameEngine->getMultiplayers().empty()) {
            globalGameEngine->getMultiplayers()[0]->setPlayerid(0);
        }
        if (globalGameEngine->getMultiplayers().size() > 1) {
            globalGameEngine->getMultiplayers()[1]->setPlayerid(1);
        }
		return_is_pressed = true; // Indicate that the players have been chosen
		inSelection = false; // Exit selection mode
    }
}
