#include "EditorEngine.h"

EditorEngine* globalEditorEngine = nullptr;

EditorEngine::EditorEngine()
	: camera() {
	globalEditorEngine = this;
	tileGrid.resize(30, std::vector<Blocks*>(100, nullptr)); // Initialize a 30x100 grid
	decor.clear();
	enemies.clear();

	populateTiles();
	populateEnemy();
}

EditorEngine::~EditorEngine() {
	for (size_t i = 0; i < tileGrid.size(); i++) {
		for (size_t j = 0; j < tileGrid[i].size(); j++) {
			delete tileGrid[i][j];
		}
	}
	tileGrid.clear();
	for (auto& dec : decor) {
		delete dec;
	}
	decor.clear();
	for (auto& enemy : enemies) {
		delete enemy;
	}
	enemies.clear();
}

void EditorEngine::populateTiles() {
	float startX = 20;
	float startY = 250;
	for (int i = 0; i < 12; i++) { tiles.push_back({ i, { startX + i * 36, startY, 32, 32 } }); }
	startY += 36;
	for (int i = 26; i < 38; i++) { tiles.push_back({ i, { startX + (i - 26) * 36, startY, 32, 32 } }); }
	startY += 36;
	for (int i = 52; i < 64; i++) { tiles.push_back({ i, { startX + (i - 52) * 36, startY, 32, 32 } }); }
	startY += 36;
	for (int i = 78; i < 90; i++) { tiles.push_back({ i, { startX + (i - 78) * 36, startY, 32, 32 } }); }

	startY += 36 + 8;
	for (int i = 12; i < 16; i++) { tiles.push_back({ i, { startX + ((i - 12) % 2) * 34, startY + ((i - 12) / 2) * 34, 32, 32 } }); }
	startX += 36 * 2;
	for (int i = 38; i < 42; i++) { tiles.push_back({ i, { startX + ((i - 38) % 2) * 34, startY + ((i - 38) / 2) * 34, 32, 32 } }); }
	startX += 36 * 2;
	for (int i = 90; i < 94; i++) { tiles.push_back({ i, { startX + ((i - 90) % 2) * 34, startY + ((i - 90) / 2) * 34, 32, 32 } }); }
	startX += 36 * 2;
	tiles.push_back({ 16, { startX, startY, 32, 32 } });
	tiles.push_back({ 17, { startX, startY + 34, 32, 32 } });
	tiles.push_back({ 18, { startX + 34, startY, 32, 32 } });
	tiles.push_back({ 19, { startX + 34, startY + 34, 32, 32 } });
	tiles.push_back({ 42, { startX + 68, startY, 32, 32 } });
	tiles.push_back({ 43, { startX + 68, startY + 34, 32, 32 } });
	tiles.push_back({ 94, { startX + 102, startY, 32, 32 } });
	tiles.push_back({ 95, { startX + 102, startY + 34, 32, 32 } });
	tiles.push_back({ 96, { startX + 136, startY, 32, 32 } });
	tiles.push_back({ 97, { startX + 136, startY + 34, 32, 32 } });
	tiles.push_back({ 68, { startX + 170, startY, 32, 32 } });
	tiles.push_back({ 69, { startX + 170, startY + 34, 32, 32 } });

	startX = 20; startY += 36 * 2 + 8;
	for (int i = 20; i < 23; i++) { tiles.push_back({ i, { startX + (i - 20) * 34, startY, 32, 32 } }); }
	startX += 36 * 3;
	for (int i = 46; i < 49; i++) { tiles.push_back({ i, { startX + (i - 46) * 34, startY, 32, 32 } }); }
	startX = 20; startY += 36;
	for (int i = 72; i < 75; i++) { tiles.push_back({ i, { startX + (i - 72) * 34, startY, 32, 32 } }); }
	startX += 36 * 3;
	for (int i = 98; i < 101; i++) { tiles.push_back({ i, { startX + (i - 98) * 34, startY, 32, 32 } }); }

	// decor
	startX = 20 + 36 * 6 + 16; startY -= 36;
	for (int i = 23; i < 26; i++) { tiles.push_back({ i, { startX + (i - 23) * 34, startY, 32, 32 } }); }
	startY += 36;
	tiles.push_back({ 111, { startX, startY, 32, 32 } });
	tiles.push_back({ 112, { startX + 34, startY, 32, 32 } });
	startX += 36 * 3 + 8; startY -= 36;
	tiles.push_back({ 107, { startX, startY, 32, 32 } });
	tiles.push_back({ 106, { startX, startY + 34, 32, 32 } });
	tiles.push_back({ 109, { startX + 36, startY, 32, 32 } });
	tiles.push_back({ 108, { startX + 36, startY + 34, 32, 32 } });
	decorTiles = { 23, 24, 25, 111, 112, 107, 106, 109, 108 };

	// special
	startX = 20; startY += 36 * 2 + 8;
	tiles.push_back({ 104, { startX, startY, 32, 32 } });
	tiles.push_back({ 110, { startX, startY + 34, 32, 32 } });
	tiles.push_back({ 105, { startX + 36, startY, 32, 32 } });
	tiles.push_back({ 113, { startX + 40, startY + 36, 32, 32 } });
	tiles.push_back({ 114, { startX + 72, startY, 32, 32 } });
	tiles.push_back({ 115, { startX + 108, startY, 32, 32 } });
	tiles.push_back({ 117, { startX + 144, startY, 32, 32 } });
}

void EditorEngine::populateEnemy() {
	float startX = 30;
	float startY = 280;
	Texture2D tex;

	tex = RESOURCE_MANAGER.getTexture("Goomba_RIGHT_0");
	enemy.push_back({ "Goomba", tex, { startX, startY,(float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("FlyingGoomba_RIGHT_0");
	enemy.push_back({ "FlyingGoomba", tex, { startX + 54, startY - 18, (float)tex.width, (float)tex.height } });

	startY += 48;
	tex = RESOURCE_MANAGER.getTexture("GreenKoopa_RIGHT_0");
	enemy.push_back({ "GreenKoopa", tex, { startX, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("RedKoopa_RIGHT_0");
	enemy.push_back({ "RedKoopa", tex, { startX + 48, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("YellowKoopa_RIGHT_0");
	enemy.push_back({ "YellowKoopa", tex, { startX + 96, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("BlueKoopa_RIGHT_0");
	enemy.push_back({ "BlueKoopa", tex, { startX + 144, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("ParaKoopaRed_RIGHT_0");
	enemy.push_back({ "ParaKoopaRed", tex, { startX + 198, startY + 4, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("ParaKoopaGreen_RIGHT_0");
	enemy.push_back({ "ParaKoopaGreen", tex, { startX + 252, startY + 4, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("ParaKoopaYellow_RIGHT_0");
	enemy.push_back({ "ParaKoopaYellow", tex, { startX + 306, startY + 4, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("ParaKoopaBlue_RIGHT_0");
	enemy.push_back({ "ParaKoopaBlue", tex, { startX + 360, startY + 4, (float)tex.width, (float)tex.height } });

	startY += 80;
	tex = RESOURCE_MANAGER.getTexture("Spiny_RIGHT_0");
	enemy.push_back({ "Spiny", tex, { startX, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("Muncher_0");
	enemy.push_back({ "Muncher", tex, { startX + 48, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("BuzzyBeetle_RIGHT_0");
	enemy.push_back({ "BuzzyBeetle", tex, { startX + 96, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("DryBones_RIGHT_0");
	enemy.push_back({ "DryBones", tex, { startX + 144, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("BobOmb_RIGHT_0");
	enemy.push_back({ "BobOmb", tex, { startX + 192, startY, (float)tex.width, (float)tex.height } });

	startY += 48;
	tex = RESOURCE_MANAGER.getTexture("PiranhaPlant_OPEN");
	enemy.push_back({ "PiranhaPlant", tex, { startX, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("FirePiranhaPlant_CLOSED");
	enemy.push_back({ "FirePiranhaPlant", tex, { startX + 48, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("PiranhaPlant_JUMP_UP_0");
	enemy.push_back({ "JumpingPiranhaPlant", tex, { startX + 96, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("Rex_RIGHT_0");
	enemy.push_back({ "Rex", tex, { startX + 48 * 4, startY, (float)tex.width, (float)tex.height } });


	startY += 96;
	tex = RESOURCE_MANAGER.getTexture("boomboom_walk_left_0");
	enemy.push_back({ "BoomBoom", tex, { startX, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("petey_walk_right_0");
	enemy.push_back({ "PeteyPiranha", tex, { startX + 80, startY, (float)tex.width , (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("Bullet_LEFT");
	enemy.push_back({ "Bullet", tex, { startX + 160, startY, (float)tex.width, (float)tex.height } });
	tex = RESOURCE_MANAGER.getTexture("BanzaiBill_LEFT");
	enemy.push_back({ "BanzaiBill", tex, { startX + 208, startY, (float)tex.width, (float)tex.height } });
}

//-----------------

void EditorEngine::update() {
	camera.handleInput();
}

void EditorEngine::handleInput() {
	Vector2 mousePos = GetMousePosition();

	// Check if tile selector is clicked
	if (displayMode == 0) {
		for (const auto& tile : tiles) {
			if (CheckCollisionPointRec(mousePos, tile.rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				selectedBlockId = tile.id;
				selectedEnemyName = "---"; 
				return;
			}
		}
	} else if (displayMode == 1) {
		for (const auto& enemySelector : enemy) {
			if (CheckCollisionPointRec(mousePos, enemySelector.rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				selectedEnemyName = enemySelector.name;
				selectedEnemyTexture = enemySelector.tex;
				selectedBlockId = -1;
				return;
			}
		}
	}
	

	// Draw
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 co = PosToCoordinate(GetMousePosition());
		int x = (int)co.x / 32;
		int y = (int)co.y / 32;

		if (selectedBlockId != -1) {
			if (x >= 0 && x < tileGrid[0].size() && y >= 0 && y < tileGrid.size()) {
				if (tileGrid[y][x] != nullptr) {
					delete tileGrid[y][x]; // Delete existing block
				}

				if (selectedBlockId == 105) {
					ItemBlock* itemBlock = dynamic_cast<ItemBlock*>(BlockFactory::getInstance().createBlock(ITEMBLOCK,
						{ (float)x * 32, (float)y * 32 }, { 32, 32 }));
					itemBlock->setTexture(RESOURCE_MANAGER.getTexture("TILE_105"));
					itemBlock->setId(selectedBlockId);
					tileGrid[y][x] = itemBlock; 
					return;
				}

				SolidBlock* solidBlock = dynamic_cast<SolidBlock*>(BlockFactory::getInstance().createBlock(SOLIDBLOCK,
					{ (float)x * 32, (float)y * 32 }, { 32, 32 }));
				solidBlock->setTexture(RESOURCE_MANAGER.getTexture("TILE_" + std::to_string(selectedBlockId)));
				solidBlock->setId(selectedBlockId);
				tileGrid[y][x] = solidBlock; // Create new block
			}
		}
		else if (selectedEnemyName != "---") {
			if (x >= 0 && x < tileGrid[0].size() && y >= 0 && y < tileGrid.size()) {
				bool exists = false;
				for (auto* enemy : enemies) {
					int ex = (int)(enemy->getPosition().x / 32);
					int ey = (int)(enemy->getPosition().y / 32);
					if (ex == x && ey == y) {
						exists = true;
						break;
					}
				}

				if (!exists) {
					if (selectedEnemyName == "Goomba") {
						enemies.push_back(new Goomba({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "FlyingGoomba") {
						enemies.push_back(new FlyingGoomba({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "GreenKoopa") {
						enemies.push_back(new GreenKoopa({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "RedKoopa") {
						enemies.push_back(new RedKoopa({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "YellowKoopa") {
						enemies.push_back(new YellowKoopa({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "BlueKoopa") {
						enemies.push_back(new BlueKoopa({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "ParaKoopaRed") {
						enemies.push_back(new ParaKoopaRed({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "ParaKoopaGreen") {
						enemies.push_back(new ParaKoopaGreen({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "ParaKoopaYellow") {
						enemies.push_back(new ParaKoopaYellow({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "ParaKoopaBlue") {
						enemies.push_back(new ParaKoopaBlue({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "Spiny") {
						enemies.push_back(new Spiny({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "Muncher") {
						enemies.push_back(new Muncher({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "BuzzyBeetle") {
						enemies.push_back(new BuzzyBeetle({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					} 
					else if (selectedEnemyName == "DryBones") {
						enemies.push_back(new DryBones({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					} 
					else if (selectedEnemyName == "BobOmb") {
						enemies.push_back(new BobOmb({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "PiranhaPlant") {
						enemies.push_back(new PiranhaPlant({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					} 
					else if (selectedEnemyName == "Rex") {
						enemies.push_back(new Rex({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "FirePiranhaPlant") {
						enemies.push_back(new FirePiranhaPlant({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "JumpingPiranhaPlant") {
						enemies.push_back(new JumpingPiranhaPlant({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "BoomBoom") {
						enemies.push_back(new BoomBoom({ (float)x * 32, (float)y * 32 }));
					}
					else if (selectedEnemyName == "PeteyPiranha") {
						enemies.push_back(new PeteyPiranha({ (float)x * 32, (float)y * 32 }));
					}
					else if (selectedEnemyName == "Bullet") {
						enemies.push_back(new Bullet({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
					else if (selectedEnemyName == "BanzaiBill") {
						enemies.push_back(new BanzaiBill({ (float)x * 32, (float)y * 32 },
							selectedEnemyTexture));
					}
				}
			}
		}
	}

	// Delete
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsKeyDown(KEY_LEFT_ALT)) {
		selectedBlockId = -1; // Deselect block
		selectedEnemyName = "---"; // Deselect enemy

		Vector2 co = PosToCoordinate(GetMousePosition());
		int x = (int)co.x / 32;
		int y = (int)co.y / 32;

		if (x >= 0 && x < tileGrid[0].size() && y >= 0 && y < tileGrid.size()) {
			if (tileGrid[y][x] != nullptr) {
				delete tileGrid[y][x]; 
				tileGrid[y][x] = nullptr; 
			}
		}
		for (auto it = enemies.begin(); it != enemies.end();) {
			if ((*it)->getPosition().x / 32 == x && (*it)->getPosition().y / 32 == y) {
				delete *it; // Delete enemy
				it = enemies.erase(it); // Remove from vector
			}
			else { ++it; }
		}
	}

	// Edit item block 
	if (IsKeyPressed(KEY_E)) {
		Vector2 co = PosToCoordinate(GetMousePosition());
		int x = (int)co.x / 32;
		int y = (int)co.y / 32;
		if (x >= 0 && x < tileGrid[0].size() && y + 1 >= 0 && y + 1 < tileGrid.size()) {
			if (tileGrid[y][x] != nullptr && dynamic_cast<ItemBlock*>(tileGrid[y][x]) != nullptr) {
				ItemBlock* itemBlock = dynamic_cast<ItemBlock*>(tileGrid[y][x]);
				currentItemBlock = itemBlock;
				popupPos = GetMousePosition();   // capture position here
				isEditingItemBlock = true;
			}
		}
	}
}

bool EditorEngine::run() {
	RESOURCE_MANAGER.stopCurrentMusic();
	RESOURCE_MANAGER.playMusic("MUSIC_5");
	while (!WindowShouldClose()) {
		if (SETTING.isMusicEnabled()) {
			UpdateMusicStream(RESOURCE_MANAGER.getMusic("MUSIC_5"));
		}
		update();
		handleInput();
		if (IsKeyPressed(KEY_ESCAPE) || GUI::back_editor_is_pressed) {
			if (GUI::back_editor_is_pressed)
				GUI::back_editor_is_pressed = false; // Reset the flag
			return false; // Exit the editor
		}
		draw();
		EndDrawing();
	}
	return true; // Return true to indicate the loop should continue
}

void EditorEngine::clear()	 {
	for (size_t i = 0; i < tileGrid.size(); i++) {
		for (size_t j = 0; j < tileGrid[i].size(); j++) {
			delete tileGrid[i][j];
			tileGrid[i][j] = nullptr;
		}
	}
	tileGrid.clear();
	decor.clear();
	enemies.clear();
	selectedBlockId = -1;
}

void EditorEngine::drawGrid() {
	const int tileSize = 32;
	Rectangle view = camera.getViewRect();
	// draw view
	DrawRectangleLinesEx(view, 1, RED); // Draw the view rectangle

	int maxCols = tileGrid[0].size();  
	int maxRows = tileGrid.size();     

	// Round view to tile coordinates
	int startX = std::max((int)(view.x / tileSize) - 1, 0);
	int startY = std::max((int)(view.y / tileSize) - 1, 0);
	int endX = std::min((int)((view.x + view.width) / tileSize) + 1, maxCols);
	int endY = std::min((int)((view.y + view.height) / tileSize) + 1, maxRows);

	for (int x = startX; x <= endX; ++x) {
		DrawLine(x * tileSize, startY * tileSize, x * tileSize, endY * tileSize, BLACK);
	}
	for (int y = startY; y <= endY; ++y) {
		DrawLine(startX * tileSize, y * tileSize, endX * tileSize, y * tileSize, BLACK);
	}

	// Debug
	
	//for (int y = startY; y < endY; ++y) {
	//	for (int x = startX; x < endX; ++x) {
	//		std::string coord = "(" + std::to_string(x) + "," + std::to_string(y) + ")";
	//		DrawText(coord.c_str(), x * tileSize + 2, y * tileSize + 2, 10, DARKGRAY);
	//	}
	//}
}

void EditorEngine::resizeGrid(int newWidth) {
	if (newWidth <= 0) return; 
	// Resize tile grid
	for (auto& row : tileGrid) {
		row.resize(newWidth, nullptr); // Initialize with nullptr
	}
	width = newWidth; // Update width
}

void EditorEngine::draw() {
	camera.beginDrawing();
	ClearBackground(WHITE);
	// Draw the tile grid
	for (size_t i = 0; i < tileGrid.size(); i++) {
		for (size_t j = 0; j < tileGrid[i].size(); j++) {
			if (tileGrid[i][j] != nullptr) {
				tileGrid[i][j]->draw();
			}
		}
	}
	// Draw enemies
	for (auto& enemy : enemies) {
		if (enemy) enemy->draw();
		//DrawRectangle(enemy->getPosition().x, enemy->getPosition().y, 32, 32, RED); // Placeholder for enemy drawing
		//DrawTexture(enemy->getCurrTexture(), enemy->getPosition().x, enemy->getPosition().y, WHITE);
	}
	drawGrid();
	camera.endDrawing();

	GUI::drawEditorUI();
	// Draw current selection
	if (selectedBlockId >= 0 && displayMode == 0) {
		Vector2 co = PosToCoordinate(GetMousePosition());

		// Now re-project back to screen position for drawing
		Vector2 screenPos = GetWorldToScreen2D(co, camera.GetCamera2D());

		// Scale by zoom to match actual size on screen
		float scale = camera.GetCamera2D().zoom;

		Texture2D tex = RESOURCE_MANAGER.getTexture("TILE_" + std::to_string(selectedBlockId));
		Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };
		Rectangle dst = { screenPos.x, screenPos.y, 32 * scale, 32 * scale };

		DrawTexturePro(tex, src, dst, { 0, 0 }, 0.0f, Fade(WHITE, 0.5f));

		// Draw the seleced block ID
		/*std::string blockIdText = "Selected Block ID: " + std::to_string(selectedBlockId);
		DrawText(blockIdText.c_str(), 10, 650, 20, BLACK);*/
	} else if (selectedEnemyName != "---" && displayMode == 1) {
		Vector2 co = PosToCoordinate(GetMousePosition());
		Vector2 screenPos = GetWorldToScreen2D(co, camera.GetCamera2D());

		float scale = camera.GetCamera2D().zoom;

		Texture2D tex = selectedEnemyTexture;
		Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };
		Rectangle dst = { screenPos.x, screenPos.y, tex.width * scale, tex.height * scale };

		DrawTexturePro(tex, src, dst, { 0, 0 }, 0.0f, Fade(WHITE, 0.5f));

		// Draw the selected enemy name
		/*
		std::string enemyNameText = "Selected Enemy: " + globalEditorEngine->getSelectedEnemyName();
		DrawText(enemyNameText.c_str(), 10, 650, 20, BLACK);
		DrawTexture(selectedEnemyTexture, 300, 650, WHITE);*/
	} else {
		Vector2 co = PosToCoordinate(GetMousePosition());
		Vector2 screenPos = GetWorldToScreen2D(co, camera.GetCamera2D());
		// Draw a rectangle at the mouse position
		float scale = camera.GetCamera2D().zoom;
		Rectangle rect = { screenPos.x, screenPos.y, 32 * scale, 32 * scale };
		DrawRectangleLinesEx(rect, 2, GREEN); // Draw a green rectangle outline
	}

	// Draw item block editing popup
	if (isEditingItemBlock && currentItemBlock) {
		ITEM_TYPE choice = POWERITEM;
		int subType = 0;
		GUI::drawItemChoice(popupPos, choice); // always draw at fixed pos
		if (choice != POWERITEM) {
			currentItemBlock->setItem(choice, 0);
			isEditingItemBlock = false;
		}
	}
}

Vector2 EditorEngine::PosToCoordinate(Vector2 pos) {
	// Get world position from mouse
	Vector2 worldPos = GetScreenToWorld2D(pos, camera.GetCamera2D());

	float posX = worldPos.x;
	float posY = worldPos.y;
	// Snap to grid
	posX = static_cast<int>((posX + 16) / 32) * 32;
	posY = static_cast<int>((posY + 16) / 32) * 32;

	return { posX, posY };
}

//--------------------

void EditorEngine::saveToJson(int slot) {
	nlohmann::json mapJson;
	mapJson["width"] = tileGrid[0].size();
	mapJson["height"] = tileGrid.size();
	mapJson["tilewidth"] = 32;
	mapJson["tileheight"] = 32;

	// Create layers
	nlohmann::json layers;

	nlohmann::json tileData;
	nlohmann::json objectData = nlohmann::json::array();
	nlohmann::json decorData;
	for (int y = 0; y < tileGrid.size(); ++y) {
		for (int x = 0; x < tileGrid[y].size(); ++x) {
			auto* block = tileGrid[y][x];
			if (block) {
				if (block->getId() == 105) {
					// Save as object instead of tile
					nlohmann::json obj;
					block->saveEntity(obj); 
					obj["x"] = x * 32;
					obj["y"] = y * 32 + 32;
					obj["type"] = "ItemBlock";
					objectData.push_back(obj);

					tileData.push_back(0); // Empty tile 
					decorData.push_back(0); // Empty decor
				}
				else if (decorTiles.find(block->getId()) != decorTiles.end()) {
					decorData.push_back(block->getId() + 1); 
					tileData.push_back(0); // Empty tile
				}
				else { 
					tileData.push_back(block->getId() + 1); 
					decorData.push_back(0); // Empty decor
				}
			}
			else { 
				tileData.push_back(0); 
				decorData.push_back(0);
			}
		}
	}

	for (auto& dec : decor) {
		if (dec) {
			int blockId = dec->getId() + 1; // Adjust for zero-based index
			int x = (int)(dec->getPosition().x / 32);
			int y = (int)(dec->getPosition().y / 32);
			if (x >= 0 && x < tileGrid[0].size() && y >= 0 && y < tileGrid.size()) {
				decorData[y * tileGrid[0].size() + x] = blockId; // Set decor block
			}
		}
	}

	for (auto& enemy : enemies) {
		nlohmann::json obj;
		enemy->saveEntity(obj);
		obj["x"] = enemy->getPosition().x;
		obj["y"] = enemy->getPosition().y + 32;
		objectData.push_back(obj);
	}

	mapJson["layers"] = nlohmann::json::array();
	mapJson["layers"].push_back({
		{"name", "TileLayer"},
		{"type", "tilelayer"},
		{"data", tileData}
		});
	mapJson["layers"].push_back({
		{"name", "ObjectLayer"},
		{"type", "objectgroup"},
		{"objects", objectData}
		});
	mapJson["layers"].push_back({
		{"name", "DecorLayer"},
		{"type", "tilelayer"},
		{"data", decorData}
		});

	std::string filename = "resources/maps/emap_" + std::to_string(slot) + ".json";
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open file for writing: " << filename << std::endl;
		return;
	}
	file << mapJson.dump(3); 
	file.close();
}

void EditorEngine::loadFromJson(int slot) {
	clear();
	std::string filename = "resources/maps/emap_" + std::to_string(slot) + ".json";
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open file for reading: " << filename << std::endl;
		return;
	}
	
	nlohmann::json mapJson;
	file >> mapJson;

	width = mapJson["width"];
	height = mapJson["height"];
	tileGrid.resize(height, std::vector<Blocks*>(width, nullptr));

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int blockId = mapJson["layers"][0]["data"][y * width + x];
			if (blockId > 0) {
				blockId--; // Adjust for zero-based index
				SolidBlock* solidBlock = dynamic_cast<SolidBlock*>(BlockFactory::getInstance().createBlock(SOLIDBLOCK,
					{ (float)x * 32, (float)y * 32 }, { 32, 32 }));
				solidBlock->setTexture(RESOURCE_MANAGER.getTexture("TILE_" + std::to_string(blockId)));
				solidBlock->setId(blockId);
				tileGrid[y][x] = solidBlock;
			}
		}
	}

	if (mapJson["layers"].size() < 2) { return; } // No object layer found
	for (auto& obj : mapJson["layers"][1]["objects"]) {
		std::string name;
		std::string type;

		// Extract Name/Type from properties array
		if (obj.contains("properties") && obj["properties"].is_array()) {
			for (auto& prop : obj["properties"]) {
				if (prop["name"] == "Name") {
					name = prop["value"];
				}
				else if (prop["name"] == "Type") {
					type = prop["value"];
				}
			}
		}
		printf("Object: %s, Type: %s\n", name.c_str(), type.c_str());

		if (name == "QuestionBlock") {
			int x = obj["x"] / 32;
			int y = obj["y"] / 32 - 1;

			ItemBlock* itemBlock = dynamic_cast<ItemBlock*>(BlockFactory::getInstance().createBlock(ITEMBLOCK,
				{ (float)x * 32, (float)y * 32 }, { 32, 32 }));
			itemBlock->loadEntity(obj);
			itemBlock->setId(105);
			itemBlock->setTexture(RESOURCE_MANAGER.getTexture("TILE_105"));
			tileGrid[y][x] = itemBlock;
		}

		if (name == "Enemy") {
			int x = obj["x"] / 32;
			int y = obj["y"] / 32 - 1;

			if (type == "Goomba") {
				enemies.push_back(new Goomba(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("Goomba_RIGHT_0")));
			}
			if (type == "FlyingGoomba") {
				enemies.push_back(new FlyingGoomba(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("FlyingGoomba_RIGHT_0")));
			}
			if (type == "GreenKoopa") {
				enemies.push_back(new GreenKoopa(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("GreenKoopa_RIGHT_0")));
			}
			if (type == "RedKoopa") {
				enemies.push_back(new RedKoopa(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("RedKoopa_RIGHT_0")));
			}
			if (type == "YellowKoopa") {
				enemies.push_back(new YellowKoopa(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("YellowKoopa_RIGHT_0")));
			}
			if (type == "BlueKoopa") {
				enemies.push_back(new BlueKoopa(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("BlueKoopa_RIGHT_0")));
			}
			if (type == "ParaKoopaRed") {
				enemies.push_back(new ParaKoopaRed(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("ParaKoopaRed_RIGHT_0")));
			}
			if (type == "ParaKoopaGreen") {
				enemies.push_back(new ParaKoopaGreen(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("ParaKoopaGreen_RIGHT_0")));
			}
			if (type == "ParaKoopaYellow") {
				enemies.push_back(new ParaKoopaYellow(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("ParaKoopaYellow_RIGHT_0")));
			}
			if (type == "ParaKoopaBlue") {
				enemies.push_back(new ParaKoopaBlue(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("ParaKoopaBlue_RIGHT_0")));
			}
			if (type == "Spiny") {
				enemies.push_back(new Spiny(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("Spiny_RIGHT_0")));
			}
			if (type == "Muncher") {
				enemies.push_back(new Muncher(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("Muncher_0")));
			}
			if (type == "BuzzyBeetle") {
				enemies.push_back(new BuzzyBeetle(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("BuzzyBeetle_RIGHT_0")));
			}
			if (type == "DryBones") {
				enemies.push_back(new DryBones(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("DryBones_0")));
			}
			if (type == "BobOmb") {
				enemies.push_back(new BobOmb(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("BobOmb_RIGHT_0")));
			}
			if (type == "PiranhaPlant") {
				enemies.push_back(new PiranhaPlant(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("PiranhaPlant_OPEN")));
			}
			if (type == "Rex") {
				enemies.push_back(new Rex(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("Rex_RIGHT_0")));
			}
			if (type == "FirePiranhaPlant") {
				enemies.push_back(new FirePiranhaPlant(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("FirePiranhaPlant_CLOSED")));
			}
			if (type == "JumpingPiranhaPlant") {
				enemies.push_back(new JumpingPiranhaPlant(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("PiranhaPlant_JUMP_UP_0")));
			}
			if (type == "BoomBoom") {
				enemies.push_back(new BoomBoom(Vector2{ (float)x * 32, (float)y * 32 }));
			}
			if (type == "PeteyPiranha") {
				enemies.push_back(new PeteyPiranha(Vector2{ (float)x * 32, (float)y * 32 }));
			}
			if (type == "Bullet") {
				enemies.push_back(new Bullet(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("Bullet_LEFT")));
			}
			if (type == "BanzaiBill") {
				enemies.push_back(new BanzaiBill(Vector2{ (float)x * 32, (float)y * 32 }, RESOURCE_MANAGER.getTexture("BanzaiBill_LEFT")));
			}
		}

	}

	if (mapJson["layers"].size() < 3) { return; } // No decor layer found
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int blockId = mapJson["layers"][2]["data"][y * width + x];
			if (blockId > 0) {
				blockId--; // Adjust for zero-based index
				DecorBlock* decorBlock = dynamic_cast<DecorBlock*>(BlockFactory::getInstance().createBlock(DECOR,
					{ (float)x * 32, (float)y * 32 }, { 32, 32 }));
				decorBlock->setTexture(RESOURCE_MANAGER.getTexture("TILE_" + std::to_string(blockId)));
				decorBlock->setId(blockId);
				decor.push_back(decorBlock);

				int x = (int)(decorBlock->getPosition().x / 32);
				int y = (int)(decorBlock->getPosition().y / 32);
				tileGrid[y][x] = decorBlock;
			}
		}
	}

	file.close();
}
