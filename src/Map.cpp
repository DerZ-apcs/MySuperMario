#include "../include/Map.h"

const std::string Map::basePath = std::string(GetWorkingDirectory()) + "/resources/maps/";

Map::Map()
{
	BgWidth = (float)GetScreenWidth();
	BgHeight = (float)GetScreenHeight();
	width = BgWidth;
	height = BgHeight;
	background = RESOURCE_MANAGER.getTexture("BACKGROUND_1");
	BackGroundPos = { {0, 0}, {BgWidth, 0}, {BgWidth * 2, 0}};
}

Map::~Map()
{
	clear();
}

std::vector<Tile*>* Map::getVectorTiles()
{
	return &tiles;
}

void Map::AddTile(Vector2 pos, TileType type, const std::string& name)
{
	tiles.push_back(new Tile(pos, type, name));
}

void Map::clear() {
	for (auto& tile : tiles) {
		delete tile;
		tile = nullptr;
	}
	tiles.clear();
	blockArray.clear();
	items.clear();
	decors.clear();
	enemies.clear();
}

void Map::drawMap()
{
	for (Entity* entity : blockArray)
		entity->draw();
}

void Map::drawBackGround() 
{
	if (background.id > 0) {
		for (int i = 0; i < 3; i++) {
			DrawTexturePro(background, { 0, 0, (float)background.width, (float)background.height },
				{ BackGroundPos[i].x, BackGroundPos[i].y + 200, (float)GetScreenWidth(), (float)GetScreenHeight()},
				{ 0, 0 }, 0.0f, WHITE);
		}
	}
	else {
		cout << "Background not found" << endl;
	}
}

void Map::drawBackGround(Vector2 cameraSize, float scale)
{
	if (background.id > 0) {
		for (int i = 0; i < 3; i++) {
			DrawTexturePro(background, 
				{ 0, 0, (float)background.width, (float)background.height },
				{ BackGroundPos[i].x, BackGroundPos[i].y + 200, (float)cameraSize.x, (float)cameraSize.y},
				{ 0, 0 }, 0.0f, WHITE);
		}
	}
	else {
		cout << "Background not found" << endl;
	}
}


void Map::LoadFromJsonFile(const std::string& filepath)
{
	clear();
	std::ifstream file(filepath);
	if (!file) {
		std::cerr << "Could not open json file " << filepath << std::endl;
		return;
	}
	nlohmann::json mapJson;
	file >> mapJson;

	int width = mapJson["width"];
	int height = mapJson["height"];
	int blockwidth = mapJson["tilewidth"];
	std::vector<int> data = mapJson["layers"][0]["data"];

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int blockId = data[static_cast<std::vector<int, std::allocator<int>>::size_type>(y) * width + x];
			if (blockId != 0) {
				Blocks* solidBlocks = new SolidBlock({ (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }, "TILE_" + std::to_string(blockId - 2));
				blockArray.push_back(solidBlocks);
			}
		}
	}
	setMapSize(Vector2{(float) width * blockwidth, (float) height * blockwidth});

}

void Map::loadBackgroundTexture(const std::string& backgroundName)
{
	background = RESOURCE_MANAGER.getTexture(backgroundName);
	if (background.id == 0) {
		throw std::runtime_error("Failed to load background texture: " + backgroundName);
	}
}

Vector2 Map::getMapSize() const
{
	return Vector2{ width, height };
}

void Map::setMapSize(Vector2 size)
{
	width = size.x;
	height = size.y;
}

bool Map::LoadFromJsonFile(std::ifstream& file, std::vector<Blocks*>& blocks, std::vector<Enemy*>& enemies, std::vector<Item*>& items, std::vector<Blocks*>& decors)
{
	return false;
}

std::vector<Blocks*> Map::getBlocks() const
{
	return blockArray;
}

std::vector<Enemy*> Map::getEnemies() const
{
	return enemies;
}

std::vector<Item*> Map::getItems() const
{
	return items;
}

std::vector<Blocks*> Map::getDecor() const
{
	return decors;
}
