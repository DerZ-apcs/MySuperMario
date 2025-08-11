#include "EditorEngine.h"

EditorEngine* globalEditorEngine = nullptr;

EditorEngine::EditorEngine(float width, float height)
	: camera() {
	globalEditorEngine = this;
	tileGrid.resize(30, std::vector<Blocks*>(100, nullptr)); // Initialize a 30x100 grid
	decor.clear();
	enemies.clear();

	float startX = 20;
	float startY = 200;
	for (int i =  0; i < 12; i++) { tiles.push_back({ i, { startX + i * 36, startY, 32, 32 } }); }
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

//-----------------

void EditorEngine::update() {
	camera.handleInput();
}

void EditorEngine::handleInput() {
	Vector2 mousePos = GetMousePosition();

	// Check if tile selector is clicked
	for (const auto& tile : tiles) {
		if (CheckCollisionPointRec(mousePos, tile.rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			selectedBlockId = tile.id;
			return;
		}
	}

	// Draw
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 co = PosToCoordinate(GetMousePosition());
		int x = (int)co.x / 32;
		int y = (int)co.y / 32;
		//printf("Click at (%d, %d)\n", (int)co.x / 32, (int)co.y / 32);
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
	}

	// Delete
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsKeyDown(KEY_LEFT_ALT)) {
		selectedBlockId = -1; // Deselect block

		Vector2 co = PosToCoordinate(GetMousePosition());
		int x = (int)co.x / 32;
		int y = (int)co.y / 32;
		if (x >= 0 && x < tileGrid[0].size() && y >= 0 && y < tileGrid.size()) {
			if (tileGrid[y][x] != nullptr) {
				delete tileGrid[y][x]; 
				tileGrid[y][x] = nullptr; 
			}
		}
	}

	// Edit item block 
	if (IsKeyPressed(KEY_E)) {
		Vector2 co = PosToCoordinate(GetMousePosition());
		int x = (int)co.x / 32;
		int y = (int)co.y / 32;
		if (x >= 0 && x < tileGrid[0].size() && y + 1 >= 0 && y + 1 < tileGrid.size()) {
			if (tileGrid[y + 1][x] != nullptr && dynamic_cast<ItemBlock*>(tileGrid[y + 1][x]) != nullptr) {
				ItemBlock* itemBlock = dynamic_cast<ItemBlock*>(tileGrid[y + 1][x]);
				currentItemBlock = itemBlock;
				popupPos = GetMousePosition();   // capture position here
				isEditingItemBlock = true;
			}
		}
	}
}

bool EditorEngine::run() {
	while (!WindowShouldClose()) {
		update();
		handleInput();
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
	
	for (int y = startY; y < endY; ++y) {
		for (int x = startX; x < endX; ++x) {
			std::string coord = "(" + std::to_string(x) + "," + std::to_string(y) + ")";
			DrawText(coord.c_str(), x * tileSize + 2, y * tileSize + 2, 10, DARKGRAY);
		}
	}
}

void EditorEngine::draw() {
	camera.beginDrawing();
	ClearBackground(SKYBLUE);
	// Draw the tile grid
	for (size_t i = 0; i < tileGrid.size(); i++) {
		for (size_t j = 0; j < tileGrid[i].size(); j++) {
			if (tileGrid[i][j] != nullptr) {
				tileGrid[i][j]->draw();
			}
		}
	}
	// Draw decor
	for (auto& dec : decor) {
		if (dec) dec->draw();
	}
	// Draw enemies
	for (auto& enemy : enemies) {
		if (enemy) enemy->draw();
	}
	drawGrid();
	camera.endDrawing();

	GUI::drawEditorUI();
	if (selectedBlockId >= 0) {
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
		std::string blockIdText = "Selected Block ID: " + std::to_string(selectedBlockId);
		DrawText(blockIdText.c_str(), 10, 650, 20, BLACK);
	}
	else {
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

void EditorEngine::saveToJson() {
	nlohmann::json mapJson;
	mapJson["width"] = tileGrid[0].size();
	mapJson["height"] = tileGrid.size();
	mapJson["tilewidth"] = 32;
	mapJson["tileheight"] = 32;

	// Create layers
	nlohmann::json layers;

	nlohmann::json tileData;
	nlohmann::json objectData = nlohmann::json::array();
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
				}
				else { tileData.push_back(block->getId() + 1); }
			}
			else { tileData.push_back(0); }
		}
	}
	
	mapJson["layers"] = nlohmann::json::array({
		{ {"name", "TileLayer"}, {"type", "tilelayer"}, {"data", tileData} },
		{ {"name", "ObjectLayer"}, {"type", "objectgroup"}, {"objects", objectData} }
	});

	std::ofstream file("resources/maps/emap_1.json");
	if (!file.is_open()) {
		std::cerr << "Failed to open file for writing." << std::endl;
		return;
	}
	file << mapJson.dump(); 
	file.close();
}

void EditorEngine::loadFromJson() {
	clear();
	std::ifstream file("resources/maps/emap_1.json");
	if (!file.is_open()) {
		std::cerr << "Failed to open map file." << std::endl;
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
		if (obj["type"] == "ItemBlock") {
			int x = obj["x"];
			int y = obj["y"];

			ItemBlock* itemBlock = dynamic_cast<ItemBlock*>(BlockFactory::getInstance().createBlock(ITEMBLOCK,
				{ (float)x, (float)y }, { 32, 32 }));
			itemBlock->loadEntity(obj); 
			itemBlock->setId(105);
			itemBlock->setTexture(RESOURCE_MANAGER.getTexture("TILE_105")); 
			tileGrid[y / 32][x / 32] = itemBlock;
		}
	}

	file.close();
}