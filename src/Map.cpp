#include "Map.h"
#include "../include/Map.h"

const std::string Map::basePath = std::string(GetWorkingDirectory()) + "/resources/maps/";

Map::Map()
{
}

Map::~Map()
{
	clear();
}

TileType Map::StringToTileType(const std::string& str)
{
	if (str == "TILE_TYPE_NORMAL") return TileType::TILE_TYPE_NORMAL;
	if (str == "TILE_TYPE_LEFT_EDGE") return TileType::TILE_TYPE_LEFT_EDGE;
	if (str == "TILE_TYPE_RIGHT_EDGE") return TileType::TILE_TYPE_RIGHT_EDGE;
	return TileType::TILE_TYPE_NORMAL;
}

std::vector<Tile*>* Map::getVectorTiles()
{
	return &tiles;
}

std::vector<Coin*>* Map::getVectorCoins()
{
	return &coins;
}

void Map::AddTile(Vector2 pos, TileType type, const std::string& name)
{
	tiles.push_back(new Tile(pos, type, name));
}

void Map::loadFromFile(const std::string& filepath)
{
	clear();
	std::ifstream fin(filepath);
	if (!fin) {
		std::cerr << "Failed to open" << filepath << "for reading" << std::endl;
		return;
	}
	std::string line;
	while (std::getline(fin, line)) {
		if (line.empty() || line[0] == '/' || line[0] == '$')
			continue;
		std::istringstream iss(line);
		std::string name, typeStr;
		int x, y;
		if (!(iss >> name >> x >> y >> typeStr)) {
			std::cerr << "Invalid line: " << line << "\n";
			continue;
		}
		AddTile(Vector2{(float)x, (float)y}, StringToTileType(typeStr), name);
	}
	fin.close();
}

void Map::clear() {
	for (auto& tile : tiles) {
		delete tile;
		tile = nullptr;
	}
	tiles.clear();

	for (auto& coin : coins) {
		delete coin;
		coin = nullptr;
	}
	coins.clear();
}

void Map::drawMap()
{
	for (auto& tile : tiles) {
		tile->draw();
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
	int tilewidth = mapJson["tilewidth"];
	std::vector<int> data = mapJson["layers"][0]["data"];

	int firstgid = mapJson["tilesets"][0]["firstgid"];

	printf("firstgid: %d\n", firstgid);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int tileId = data[y * width + x];
			if (tileId != 0) {
				// Subtract firstgid to get 0-based index
				int texIndex = tileId - firstgid;

				if (tileId == 114) { // coin gid
					coins.push_back(new Coin(
						Vector2{ (float)x * tilewidth, (float)y * tilewidth },
						Vector2{ (float)tilewidth, (float)tilewidth },
						Vector2{ 0,0 },
						NONE,
						0.1f 
					));
				}
				else if (tileId == 105) { // brick gid
					tiles.push_back(new Brick(Vector2{ (float)x * tilewidth, (float)y * tilewidth }));
				}
				else if (tileId == 106) { // question block gid
					tiles.push_back(new QuestionBlock(Vector2{ (float)x * tilewidth, (float)y * tilewidth }));
				}
				else {
					std::string texKey = "TILE_" + std::to_string(texIndex);

					tiles.push_back(new Tile(
						Vector2{ (float)x * tilewidth, (float)y * tilewidth },
						TileType::TILE_TYPE_NORMAL,
						texKey
					));
				}
			}
		}
	}
}

