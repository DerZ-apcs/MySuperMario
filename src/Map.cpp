#include "../include/Map.h"

const std::string Map::basePath = std::string(GetWorkingDirectory()) + "/resources/maps/";

Map::Map()
{
	BgWidth = (float)GetScreenWidth();
	BgHeight = (float)GetScreenHeight();
	width = BgWidth;
	height = BgHeight;
	background = RESOURCE_MANAGER.getTexture("BACKGROUND_1");
	for (int i = 0; i < 10; i++) {
		BackGroundPos.push_back({ (float)i * BgWidth, 0 });
	}
	backGroundName = "BACKGROUND_1";
}

Map::~Map()
{
	clear();
}

void Map::clear() {
	tileGrid.clear();
	movingBlocks.clear();
	items.clear();
	decors.clear();
	enemies.clear();
	covers.clear();
	secretAreas.clear();
}

void Map::drawMap()
{
}

void Map::drawBackGround() 
{
	if (background.id > 0) {
		for (int i = 0; i < 10; i++) {
			DrawTexturePro(background, { 0, 0, (float)background.width, (float)background.height },
				{ BackGroundPos[i].x, BackGroundPos[i].y + 230, (float)GetScreenWidth(), (float)GetScreenHeight()},
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
		for (int i = 0; i < 10; i++) {
			DrawTexturePro(background, 
				{ 0, 0, (float)background.width, (float)background.height },
				{ BackGroundPos[i].x, BackGroundPos[i].y + 230, (float)cameraSize.x, (float)cameraSize.y},
				{ 0, 0 }, 0.0f, WHITE);
		}
	}
	else {
		cout << "Background not found" << endl;
	}
}
Vector2 Map::LoadMapSize(const std::string& filepath) {
	std::ifstream file(filepath);
	if (!file) {
		std::cerr << "Could not open json file" << filepath << std::endl;
		return { 0, 0 };
	}
	nlohmann::json mapJson;
	file >> mapJson;
	int width = mapJson["width"];
	int height = mapJson["height"];
	int blockwidth = mapJson["tilewidth"];
	return (Vector2{ (float)width * blockwidth, (float)height * blockwidth });
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

	int firstgid = 1;
	if (mapJson.contains("tilesets") && !mapJson["tilesets"].empty() && mapJson["tilesets"][0].contains("firstgid")) {
		firstgid = mapJson["tilesets"][0]["firstgid"].get<int>();
	}

	tileGrid.resize(height, std::vector<Blocks*>(width, nullptr));
	setMapSize(Vector2{ (float)width * blockwidth, (float)height * blockwidth });

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int blockId = data[static_cast<std::vector<int, std::allocator<int>>::size_type>(y) * width + x];
			if (blockId != 0) {
				int texId = blockId - firstgid;
				if (blockId == 105) {
					Brick* brick = dynamic_cast<Brick*>(BlockFactory::getInstance().createBlock(BRICK,
						{ (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));
					if (!brick) {
						throw std::runtime_error("Failed to create brick block: ");
					}
					brick->setTextureName("TILE_" + std::to_string(texId));
					brick->setTexture(RESOURCE_MANAGER.getTexture(brick->getTextureName().c_str()));
					tileGrid[y][x] = brick;
					continue;
				}
				if (blockId == 114) {
					Coin* coin = dynamic_cast<Coin*>(ItemFactory::getInstance().createItem(COIN,
						{ (float)x * blockwidth, (float)y * blockwidth }, LEFT, 0));
					if (!coin) {
						throw std::runtime_error("Failed to create coin: ");
					}
					items.push_back(coin);
					continue;
				}

				if (blockId == 115) {
					NoteBlock* block = dynamic_cast<NoteBlock*>(BlockFactory::getInstance().createBlock(NOTEBLOCK, 
						{(float)x * blockwidth, (float)y * blockwidth}, {32, 32}));
					if (!block) {
						throw std::runtime_error("Failed to create note block: ");
					}
					block->setTextureName("NOTE_0");
					tileGrid[y][x] = block;
					continue;
				}

				if (blockId == 116) {
					CloudBlock* cloudBlock = dynamic_cast<CloudBlock*>(BlockFactory::getInstance().createBlock(CLOUDBLOCK,
						{ (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));
					if (!cloudBlock) {
						throw std::runtime_error("Failed to create cloud block: ");
					}
					cloudBlock->setTextureName("TILE_115");
					tileGrid[y][x] = cloudBlock;
					continue;
				}

				if (blockId == 118) {
					RotatingBlock* block = dynamic_cast<RotatingBlock*>(BlockFactory::getInstance().createBlock(ROTATINGBLOCK,
						{ (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));
					if (!block) {
						throw std::runtime_error("Failed to create rotating block: ");
					}
					block->setTextureName("ROTATING_0");
					tileGrid[y][x] = block;
					continue;
				}

				// else create solid block
				SolidBlock* solidBlock = dynamic_cast<SolidBlock*>(BlockFactory::getInstance().createBlock(SOLIDBLOCK,
					{ (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));	
				solidBlock->setTextureName("TILE_" + std::to_string(texId));
				solidBlock->setTexture(RESOURCE_MANAGER.getTexture(solidBlock->getTextureName()));
				if (!solidBlock) {
					throw std::runtime_error("Failed to create solid block: ");
				}
				tileGrid[y][x] = solidBlock;
			}
		}
	}

	if (mapJson["layers"].size() < 2) { return; }
	printf("Loading objects from layer 1\n");
	nlohmann::json objectLayer = mapJson["layers"][1];
	nlohmann::json objects = objectLayer["objects"];
	for (auto& obj : objects) {
		int gid = -1;
		if (obj.contains("gid") && obj["gid"].is_number_integer()) {
			gid = obj["gid"];
		}
		int x = obj["x"] / 32;
		int y = obj["y"] / 32 - 1;

		std::string name;
		std::string type;
		for (auto& prop : obj["properties"]) {
			if (prop["name"] == "Name") name = prop["value"];
			else if (prop["name"] == "Type") type = prop["value"];
		}

		if (name == "QuestionBlock") {
			if (type == "Mushroom") {
				Blocks* block = dynamic_cast<ItemBlock*>(BlockFactory::getInstance().createBlock(ITEMBLOCK, {(float)x * blockwidth, (float)y * blockwidth}, {32, 32}));
				dynamic_cast<ItemBlock*>(block)->setItem(MUSHROOM, 0);
				if (!block) {
					throw std::runtime_error("Failed to create item block: ");
				}
				block->setTextureName("QUESTION_0");
				tileGrid[y][x] = block;
			}
			else if (type == "Flower") {
				Blocks* block = dynamic_cast<ItemBlock*>(BlockFactory::getInstance().createBlock(ITEMBLOCK, { (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));
				dynamic_cast<ItemBlock*>(block)->setItem(FLOWER, 0);
				if (!block) {
					throw std::runtime_error("Failed to create item block: ");
				}
				block->setTextureName("QUESTION_0");
				tileGrid[y][x] = block;
			}
			else if (type == "Star") {
				Blocks* block = dynamic_cast<ItemBlock*>(BlockFactory::getInstance().createBlock(ITEMBLOCK, { (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));
				dynamic_cast<ItemBlock*>(block)->setItem(STAR, 0);
				if (!block) {
					throw std::runtime_error("Failed to create item block: ");
				}
				block->setTextureName("QUESTION_0");
				tileGrid[y][x] = block;
			}
			else if (type == "Moon") {
				Blocks* block = dynamic_cast<ItemBlock*>(BlockFactory::getInstance().createBlock(ITEMBLOCK, { (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));
				dynamic_cast<ItemBlock*>(block)->setItem(MOON, 0);
				if (!block) {
					throw std::runtime_error("Failed to create item block: ");
				}
				block->setTextureName("QUESTION_0");
				tileGrid[y][x] = block;
			}
		}

		if (name == "HiddenBlock") {
			int texId = gid - firstgid;
			HiddenBlock* hiddenBlock = dynamic_cast<HiddenBlock*>(BlockFactory::getInstance().createBlock(HIDDEN, { (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));
			hiddenBlock->setTexture(RESOURCE_MANAGER.getTexture("TILE_" + std::to_string(texId)));
			hiddenBlock->setTextureName("TILE_" + std::to_string(texId));

			if (type == "ItemBlock") hiddenBlock->setRevealType(BLOCK_TYPE::ITEMBLOCK);
			else if (type == "CoinBlock") hiddenBlock->setRevealType(BLOCK_TYPE::COINBLOCK);
			else if (type == "Brick") hiddenBlock->setRevealType(BLOCK_TYPE::BRICK); 
			else hiddenBlock->setRevealType(BLOCK_TYPE::SOLIDBLOCK); 

			tileGrid[y][x] = hiddenBlock;
		}

		if (name == "MovingBlock")
		{
			MovingBlock* movingBlock = dynamic_cast<MovingBlock*>(BlockFactory::getInstance().createBlock(MOVINGBLOCK, { (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));
			
			string textureName = "MOVING_" + type;
			Texture2D tex = RESOURCE_MANAGER.getTexture(textureName);
			movingBlock->setTextureName(textureName);
			movingBlock->setTexture(tex);
			movingBlock->setSize({ (float)tex.width, (float)tex.height });

			movingBlocks.push_back(movingBlock);
		}

		if (name == "CoinBlock") {
			int texId = gid - firstgid;
			Blocks* coinBlock = dynamic_cast<CoinBlock*>(BlockFactory::getInstance().createBlock(COINBLOCK, { (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));
			coinBlock->setTexture(RESOURCE_MANAGER.getTexture("TILE_" + std::to_string(texId)));
			dynamic_cast<CoinBlock*>(coinBlock)->setCount(3); // default coin count
			if (!coinBlock) {
				throw std::runtime_error("Failed to create coin block: ");
			}
			coinBlock->setTextureName("TILE_110");
			tileGrid[y][x] = coinBlock;
		}

		if (name == "Cannon") {
			Direction direction;
			for (auto& prop : obj["properties"]) {
				if (prop["name"] == "Direction") direction = (prop["value"] == "Left") ? LEFT : RIGHT;
			}
			int bullet_t = (type == "Bullet") ? 0 : 1;
			Blocks* cannon = dynamic_cast<Cannon*>(BlockFactory::getInstance().createBlock(CANNON, { (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));
			dynamic_cast<Cannon*>(cannon)->setDirection(direction);
			dynamic_cast<Cannon*>(cannon)->setBulletType(bullet_t);
			if (!cannon) {
				throw std::runtime_error("Failed to create cannon block: ");
			}
			cannon->setTextureName("TILE_116");
			tileGrid[y][x] = cannon;
		}

		if (name == "Enemy") {
			if (type == "Goomba") {
				enemies.push_back(new Goomba(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("Goomba_RIGHT_0")));
			}
			else if (type == "FlyingGoomba") {
				enemies.push_back(new FlyingGoomba(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("FlyingGoomba_RIGHT_0")));
			}
			else if (type == "PiranhaPlant") {
				enemies.push_back(new PiranhaPlant(Vector2{ (float)x * blockwidth + 0.5f * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("PiranhaPlant_OPEN")));
			}
			else if (type == "JumpingPiranhaPlant" || type == "JumpingPiranha") {
				enemies.push_back(new JumpingPiranhaPlant(Vector2{ (float)x * blockwidth + 0.5f * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("PiranhaPlant_JUMP_UP_0")));
			}
			else if (type == "FirePiranhaPlant" || type == "FirePiranha") {
				enemies.push_back(new FirePiranhaPlant(Vector2{ (float)x * blockwidth + 0.5f * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("FirePiranhaPLant_OPEN")));
			}
			else if (type == "RapidFirePiranhaPlant" || type == "RapidFirePiranha") {
				enemies.push_back(new RapidFirePiranha(Vector2{ (float)x * blockwidth + 0.5f * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("FirePiranhaPlant_OPEN")));
			}
			else if (type == "HomingFirePiranha" || type == "HomingFirePiranhaPlant") {
				enemies.push_back(new HomingFirePiranha(Vector2{ (float)x * blockwidth + 0.5f * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("FirePiranhaPlant_OPEN")));
			}
			else if (type == "GreenKoopa" || type == "Koopa") {
				enemies.push_back(new GreenKoopa(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("GreenKoopa_RIGHT_0")));
			}
			else if (type == "RedKoopa") {
				enemies.push_back(new RedKoopa(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("RedKoopa_RIGHT_0")));
			} 
			else if (type == "YellowKoopa") {
				enemies.push_back(new YellowKoopa(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("YellowKoopa_RIGHT_0")));
			}
			else if (type == "BlueKoopa") {
				enemies.push_back(new BlueKoopa(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("BlueKoopa_RIGHT_0")));
			}
			else if (type == "ParaKoopaRed") {
				enemies.push_back(new ParaKoopaRed(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("ParaKoopaRed_RIGHT_0")));
			}
			else if (type == "ParaKoopaGreen") {
				enemies.push_back(new ParaKoopaGreen(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("ParaKoopaGreen_RIGHT_0")));
			}
			else if (type == "ParaKoopaYellow") {
				enemies.push_back(new ParaKoopaYellow(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("ParaKoopaYellow_RIGHT_0")));
			}
			else if (type == "ParaKoopaBlue") {
				enemies.push_back(new ParaKoopaBlue(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("ParaKoopaBlue_RIGHT_0")));
			}
			else if (type == "BoomBoom") {
				enemies.push_back(new BoomBoom(Vector2{ (float)x * blockwidth, (float)y * blockwidth }));
			}
			else if (type == "PeteyPiranha") {
				enemies.push_back(new PeteyPiranha(Vector2{ (float)x * blockwidth, (float)y * blockwidth }));
			}
			else if (type == "Bullet") {
				enemies.push_back(new Bullet(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("Bullet_LEFT"), LEFT));
			}
			else if (type == "BanzaiBill") {
				enemies.push_back(new BanzaiBill(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("BanzaiBill_LEFT_0")));
			}
			else if (type == "FireBullet") {
				enemies.push_back(new FireBullet(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("Bullet_LEFT"), LEFT));
			}
			else if (type == "Muncher") {
				enemies.push_back(new Muncher(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("Muncher_0")));
			}
			else if (type == "Rex") {
				enemies.push_back(new Rex(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("Rex_RIGHT_0")));
			}
			else if (type == "BuzzyBeetle") {
				enemies.push_back(new BuzzyBeetle(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("BuzzyBeetle_RIGHT_0")));
			}
			else if (type == "Spiny") {
				enemies.push_back(new Spiny(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("Spiny_RIGHT_0")));
			}
			else if (type == "DryBones") {
				enemies.push_back(new DryBones(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("DryBones_RIGHT_0")));
			}
			else if (type == "BobOmb") {
				enemies.push_back(new BobOmb(Vector2{ (float)x * blockwidth, (float)y * blockwidth }, RESOURCE_MANAGER.getTexture("BobOmb_RIGHT_0")));
			}
			else if (type == "BoomBoom") {
				enemies.push_back(new BoomBoom(Vector2{ (float)x * blockwidth, (float)y * blockwidth }));
			}
			else if (type == "PeteyPiranha") {
				enemies.push_back(new PeteyPiranha(Vector2{ (float)x * blockwidth, (float)y * blockwidth }));
			}
			else { std::cerr << "Unknown enemy type: " << type << std::endl; }
		}

		if (name == "Area") {
			int areaWidth;
			int areaHeight;
			for (auto& prop : obj["properties"]) {
				if (prop["name"] == "Width") areaWidth = prop["value"];
				else if (prop["name"] == "Height") areaHeight = prop["value"];
			}
			Rectangle area = { (float)x * blockwidth, (float)y * blockwidth, (float)areaWidth * blockwidth, (float)areaHeight * blockwidth };
			secretAreas.push_back(area);
		}
	}
	
	 //decor layer
	if (mapJson["layers"].size() < 3) { return; }
	std::vector<int> decorData = mapJson["layers"][2]["data"];
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int blockId = decorData[static_cast<std::vector<int, std::allocator<int>>::size_type>(y) * width + x];
			if (blockId != 0) {
				int texId = blockId - firstgid;
				Blocks* decorBlock = dynamic_cast<DecorBlock*>(BlockFactory::getInstance().createBlock(DECOR, { (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));
				decorBlock->setTexture(RESOURCE_MANAGER.getTexture("TILE_" + std::to_string(texId)));
				//decors.push_back(decorBlock);
				if (!decorBlock) {
					throw std::runtime_error("Failed to create decor block: ");
				}
				tileGrid[y][x] = decorBlock;
			}
		}
	}

	// covers layer
	if (mapJson["layers"].size() < 4) { return; }
	printf("Loading covers from layer 3\n");
	std::vector<int> coverData = mapJson["layers"][3]["data"];
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int blockId = coverData[static_cast<std::vector<int, std::allocator<int>>::size_type>(y) * width + x];
			if (blockId != 0) {
				int texId = blockId - firstgid;
				Blocks* coverBlock = dynamic_cast<SolidBlock*>(BlockFactory::getInstance().createBlock(SOLIDBLOCK, { (float)x * blockwidth, (float)y * blockwidth }, { 32, 32 }));
				coverBlock->setTexture(RESOURCE_MANAGER.getTexture("TILE_" + std::to_string(texId)));
				if (!coverBlock) {
					throw std::runtime_error("Failed to create cover block: ");
				}
				tileGrid[y][x] = coverBlock;
			}
		}
	}
}

void Map::loadBackgroundTexture(const std::string& backgroundName)
{
	this->backGroundName = backgroundName;
	background = RESOURCE_MANAGER.getTexture(backgroundName.c_str());
	if (background.id == 0) {
		throw std::runtime_error("Failed to load background texture: " + backgroundName);
	}
}

Vector2 Map::getMapSize() const
{
	return Vector2{ width, height };
}

Vector2 Map::getGoalPosition() const
{
	return Vector2{goalX, goalY};
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

std::vector<MovingBlock*> Map::getMovingBlocks() const
{
	return movingBlocks;
}

std::vector<std::vector<Blocks*>> Map::getTileGrid() const
{
	return tileGrid;
}

std::vector<Enemy*> Map::getEnemies() const
{
	return enemies;
}

std::vector<Item*> Map::getItems() const
{
	return this->items;
}

std::vector<Blocks*> Map::getDecor() const
{
	return decors;
}

std::vector<Blocks*> Map::getCovers() const
{
	return covers;
}

std::vector<Rectangle> Map::getSecretAreas() const
{
	return secretAreas;
}

void Map::loadMap(const json& j)
{
	width = j["width"];
	height = j["height"];
	backGroundName = j["backgroundName"];
}

void Map::saveMap(json& j) const
{
	j["width"] = width;
	j["height"] = height;
	j["backgroundName"] = backGroundName;
}
