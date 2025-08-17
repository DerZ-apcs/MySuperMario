#ifndef EDITORENGINE_H
#define EDITORENGINE_H

#include <unordered_set>
//-----------------
#include "../include/Camera.h"
#include "../include/Map.h"
#include "../include/GUI.h"

struct TileSelector {
	int id;
	Rectangle rect;
};

struct EnemySelector {
	string name;
	Texture2D tex;
	Rectangle rect;
};

class EditorEngine {
private:
	int height = 30;
	int width = 100;	

	std::vector<std::vector<Blocks*>> tileGrid; // for tile grid
	std::vector<Blocks*> decor;
	std::vector<Enemy*> enemies;

	EditorCamera camera;

	std::unordered_set<int> decorTiles;
	std::vector<TileSelector> tiles; 
	int selectedBlockId = -1; 
	void populateTiles(); 
	std::vector<EnemySelector> enemy;
	string selectedEnemyName = "---";
	Texture2D selectedEnemyTexture = RESOURCE_MANAGER.getTexture("Coin_0");
	void populateEnemy();

	int displayMode = 0; // 0: block | 1: enemy
	bool isEditingItemBlock = false;
	ItemBlock* currentItemBlock = nullptr;
	Vector2  popupPos;

public:
	EditorEngine();
	~EditorEngine();

	void draw();           // draw map + editor UI
	void drawGrid();
	void resizeGrid(int newWidth);

	const std::vector<TileSelector>& getTiles() const { return tiles; }
	const int getSelectedBlockId() const { return selectedBlockId; }

	const std::vector<EnemySelector>& getEnemy() const { return enemy; }
	const string getSelectedEnemyName() const { return selectedEnemyName; }
	const Texture2D getSelectedEnemyTexture() const { return selectedEnemyTexture; }

	const int getDisplayMode() const { return displayMode; }
	void setDisplayMode(int mode) { displayMode = mode; }

	Vector2 PosToCoordinate(Vector2 pos);

	void update();         // camera
	void handleInput();    // handle input for editor
	bool run();            
	void clear();

	void saveToJson();     // write map
	void loadFromJson();   // load map
};
extern EditorEngine* globalEditorEngine;

#endif // !EDITORENGINE_H
