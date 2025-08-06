#include "EditorEngine.h"

EditorEngine* globalEditorEngine = nullptr;

EditorEngine::EditorEngine(float width, float height)
	: camera() {
	globalEditorEngine = this;
	tileGrid.resize(30, std::vector<Blocks*>(150, nullptr)); // Initialize a 30x150 grid
	decor.clear();
	enemies.clear();

	float startX = 20;
	float startY = 200;
	for (int i = 0; i < 12; i++) {
		tiles.push_back({ i, { startX + (i % 7) * 36, startY + (i / 7) * 36, 32, 32 } });
	}
	startY += 36 * 2;
	for (int i = 26; i < 38; i++) {
		tiles.push_back({ i, { startX + ((i - 26) % 7) * 36, startY + ((i - 26) / 7) * 36, 32, 32 } });
	}
	startY += 36 * 2;
	for (int i = 52; i < 64; i++) {
		tiles.push_back({ i, { startX + ((i - 52) % 7) * 36, startY + ((i - 52) / 7) * 36, 32, 32 } });
	}
	startY += 36 * 2;
	for (int i = 78; i < 90; i++) {
		tiles.push_back({ i, { startX + ((i - 78) % 7) * 36, startY + ((i - 78) / 7) * 36, 32, 32 } });
	}
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

	// Check if tile selector (GUI sidebar) is clicked
	for (const auto& tile : tiles) {
		if (CheckCollisionPointRec(mousePos, tile.rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			selectedBlockId = tile.id;
			return;
		}
	}

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
				SolidBlock* solidBlock = dynamic_cast<SolidBlock*>(BlockFactory::getInstance().createBlock(SOLIDBLOCK,
					{ (float)x * 32, (float)y * 32 }, { 32, 32 }));
				solidBlock->setTexture(RESOURCE_MANAGER.getTexture("TILE_" + std::to_string(selectedBlockId)));
				solidBlock->setId(selectedBlockId);
				tileGrid[y][x] = solidBlock; // Create new block
			}
		}
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
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
	nlohmann::json layerData;
	for (const auto& row : tileGrid) {
		for (const auto& block : row) {
			layerData.push_back(block ? block->getId() + 1 : 0);
		}
	}
	layers.push_back({ {"data", layerData}, {"name", "TileLayer"}, {"type", "tilelayer"} });
	mapJson["layers"] = layers;
	
	std::ofstream file("resources/maps/emap_1.json");
	if (!file.is_open()) {
		std::cerr << "Failed to open file for writing." << std::endl;
		return;
	}
	file << mapJson.dump(); 
	file.close();
}