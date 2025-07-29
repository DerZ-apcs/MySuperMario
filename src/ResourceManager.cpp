#include "../include/ResourceManager.h"
#include <algorithm>

//std::map<std::string, Texture2D> ResourceManager::textures;

void ResourceManager::loadTextures() {
	// move
	textures["SmallMario_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/SmallMario_0.png");
	textures["SmallMario_RIGHT_1"] = LoadTexture("resources/images/sprites/mario/SmallMario_1.png");
	textures["SmallMario_LEFT_0"] = flipTexture(textures["SmallMario_RIGHT_0"]);
	textures["SmallMario_LEFT_1"] = flipTexture(textures["SmallMario_RIGHT_1"]);

	textures["SuperMario_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/SuperMario_0.png");
	textures["SuperMario_RIGHT_1"] = LoadTexture("resources/images/sprites/mario/SuperMario_1.png");
	textures["SuperMario_RIGHT_2"] = LoadTexture("resources/images/sprites/mario/SuperMario_2.png");
	textures["SuperMario_LEFT_0"] = flipTexture(textures["SuperMario_RIGHT_0"]);
	textures["SuperMario_LEFT_1"] = flipTexture(textures["SuperMario_RIGHT_1"]);
	textures["SuperMario_LEFT_2"] = flipTexture(textures["SuperMario_RIGHT_2"]);
	// jump
	textures["SmallMarioJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/SmallMarioJumping_0.png");
	textures["SmallMarioJumping_LEFT_0"] = flipTexture(textures["SmallMarioJumping_RIGHT_0"]);

	textures["SuperMarioJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/SuperMarioJumping_0.png");
	textures["SuperMarioJumping_LEFT_0"] = flipTexture(textures["SuperMarioJumping_RIGHT_0"]);
	// fall
	textures["SmallMarioFalling_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/SmallMarioFalling_0.png");
	textures["SmallMarioFalling_LEFT_0"] = flipTexture(textures["SmallMarioFalling_RIGHT_0"]);

	textures["SuperMarioFalling_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/SuperMarioFalling_0.png");
	textures["SuperMarioFalling_LEFT_0"] = flipTexture(textures["SuperMarioFalling_RIGHT_0"]);
	// duck
	textures["SmallMarioDucking_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/SmallMarioDucking_0.png");
	textures["SmallMarioDucking_LEFT_0"] = flipTexture(textures["SmallMarioDucking_RIGHT_0"]);

	textures["SuperMarioDucking_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/SuperMarioDucking_0.png");
	textures["SuperMarioDucking_LEFT_0"] = flipTexture(textures["SuperMarioDucking_RIGHT_0"]);

	// trasition
	textures["TransitioningMario_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/TransitioningMario_1.png");
	textures["TransitioningMario_LEFT_0"] = flipTexture(textures["TransitioningMario_RIGHT_0"]);
	textures["TransitioningFireMario_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/TransitioningFireMario.png");
	textures["TransitioningFireMario_LEFT_0"] = flipTexture(textures["TransitioningFireMario_RIGHT_0"]);

	// FireMario
	textures["Fire_Mario_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FireMario_0.png");
	textures["Fire_Mario_RIGHT_1"] = LoadTexture("resources/images/sprites/mario/FireMario_1.png");
	textures["Fire_Mario_RIGHT_2"] = LoadTexture("resources/images/sprites/mario/FireMario_2.png");
	textures["Fire_Mario_LEFT_0"] = flipTexture(textures["Fire_Mario_RIGHT_0"]);
	textures["Fire_Mario_LEFT_1"] = flipTexture(textures["Fire_Mario_RIGHT_1"]);
	textures["Fire_Mario_LEFT_2"] = flipTexture(textures["Fire_Mario_RIGHT_2"]);

	textures["Fire_Mario_Jumping_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FireMarioJumping_0.png");
	textures["Fire_Mario_Jumping_LEFT_0"] = flipTexture(textures["Fire_Mario_Jumping_RIGHT_0"]);

	textures["Fire_Mario_Falling_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FireMarioFalling_0.png");
	textures["Fire_Mario_Falling_LEFT_0"] = flipTexture(textures["Fire_Mario_Falling_RIGHT_0"]);

	textures["Fire_Mario_Ducking_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FireMario_Ducking_0.png");
	textures["Fire_Mario_Ducking_LEFT_0"] = flipTexture(textures["Fire_Mario_Ducking_RIGHT_0"]);
	// fireball
	textures["FlowerMarioFireball_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FlowerMarioFireball_0.png");
	textures["FlowerMarioFireball_RIGHT_1"] = LoadTexture("resources/images/sprites/mario/FlowerMarioFireball_1.png");
	textures["FlowerMarioFireball_RIGHT_2"] = LoadTexture("resources/images/sprites/mario/FlowerMarioFireball_2.png");
	textures["FlowerMarioFireball_RIGHT_3"] = LoadTexture("resources/images/sprites/mario/FlowerMarioFireball_3.png");
	textures["FlowerMarioFireball_LEFT_0"] = flipTexture(textures["FlowerMarioFireball_RIGHT_0"]);
	textures["FlowerMarioFireball_LEFT_1"] = flipTexture(textures["FlowerMarioFireball_RIGHT_1"]);
	textures["FlowerMarioFireball_LEFT_2"] = flipTexture(textures["FlowerMarioFireball_RIGHT_2"]);
	textures["FlowerMarioFireball_LEFT_3"] = flipTexture(textures["FlowerMarioFireball_RIGHT_3"]);

	textures["FireMarioThrowingFireball_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FireMario_Firing_0.png");
	textures["FireMarioThrowingFireball_LEFT_0"] = flipTexture(textures["FireMarioThrowingFireball_RIGHT_0"]);

	// Enemies
	textures["Goomba_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/Goomba_0.png");
	textures["Goomba_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/Goomba_1.png");
	textures["Goomba_LEFT_0"] = flipTexture(textures["Goomba_RIGHT_0"]);
	textures["Goomba_LEFT_1"] = flipTexture(textures["Goomba_RIGHT_1"]);
	textures["Goomba_Dead"] = LoadTexture("resources/images/sprites/baddies/Goomba_0.png");
	
	textures["FlyingGoomba_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/FlyingGoomba_0.png");
	textures["FlyingGoomba_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/FlyingGoomba_1.png");
	textures["FlyingGoomba_LEFT_0"] = flipTexture(textures["FlyingGoomba_RIGHT_0"]);
	textures["FlyingGoomba_LEFT_1"] = flipTexture(textures["FlyingGoomba_RIGHT_1"]);

	textures["YellowKoopa_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/YellowKoopaTroopa_0.png");
	textures["YellowKoopa_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/YellowKoopaTroopa_1.png");
	textures["YellowKoopa_LEFT_0"] = flipTexture(textures["YellowKoopa_RIGHT_0"]);
	textures["YellowKoopa_LEFT_1"] = flipTexture(textures["YellowKoopa_RIGHT_1"]);
	textures["YellowKoopa_Shell_3"] = LoadTexture("resources/images/sprites/baddies/YellowKoopaTroopa_Shell_3.png");
	textures["YellowKoopa_Shell_2"] = LoadTexture("resources/images/sprites/baddies/YellowKoopaTroopa_Shell_2.png");
	textures["YellowKoopa_Shell_1"] = LoadTexture("resources/images/sprites/baddies/YellowKoopaTroopa_Shell_1.png");
	textures["YellowKoopa_Shell_0"] = LoadTexture("resources/images/sprites/baddies/YellowKoopaTroopa_Shell_0.png");

	textures["BlueKoopa_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/BlueKoopaTroopa_0.png");
	textures["BlueKoopa_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/BlueKoopaTroopa_1.png");
	textures["BlueKoopa_LEFT_0"] = flipTexture(textures["BlueKoopa_RIGHT_0"]);
	textures["BlueKoopa_LEFT_1"] = flipTexture(textures["BlueKoopa_RIGHT_1"]);
	textures["BlueKoopa_Shell_3"] = LoadTexture("resources/images/sprites/baddies/BlueKoopaTroopa_Shell_3.png");
	textures["BlueKoopa_Shell_2"] = LoadTexture("resources/images/sprites/baddies/BlueKoopaTroopa_Shell_2.png");
	textures["BlueKoopa_Shell_1"] = LoadTexture("resources/images/sprites/baddies/BlueKoopaTroopa_Shell_1.png");
	textures["BlueKoopa_Shell_0"] = LoadTexture("resources/images/sprites/baddies/BlueKoopaTroopa_Shell_0.png");

	textures["GreenKoopa_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/GreenKoopaTroopa_0.png");
	textures["GreenKoopa_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/GreenKoopaTroopa_1.png");
	textures["GreenKoopa_LEFT_0"] = flipTexture(textures["GreenKoopa_RIGHT_0"]);
	textures["GreenKoopa_LEFT_1"] = flipTexture(textures["GreenKoopa_RIGHT_1"]);
	textures["GreenKoopa_Shell_3"] = LoadTexture("resources/images/sprites/baddies/GreenKoopaTroopa_Shell_3.png");
	textures["GreenKoopa_Shell_2"] = LoadTexture("resources/images/sprites/baddies/GreenKoopaTroopa_Shell_2.png");
	textures["GreenKoopa_Shell_1"] = LoadTexture("resources/images/sprites/baddies/GreenKoopaTroopa_Shell_1.png");
	textures["GreenKoopa_Shell_0"] = LoadTexture("resources/images/sprites/baddies/GreenKoopaTroopa_Shell_0.png");

	textures["ParaKoopaRed_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/ParaKoopaRed_0.png");
	textures["ParaKoopaRed_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/ParaKoopaRed_1.png");
	textures["ParaKoopaRed_LEFT_0"] = flipTexture(textures["ParaKoopaRed_RIGHT_0"]);
	textures["ParaKoopaRed_LEFT_1"] = flipTexture(textures["ParaKoopaRed_RIGHT_1"]);
	textures["RedKoopa_Shell_3"] = LoadTexture("resources/images/sprites/baddies/RedKoopaTroopa_Shell_3.png");
	textures["RedKoopa_Shell_2"] = LoadTexture("resources/images/sprites/baddies/RedKoopaTroopa_Shell_2.png");
	textures["RedKoopa_Shell_1"] = LoadTexture("resources/images/sprites/baddies/RedKoopaTroopa_Shell_1.png");
	textures["RedKoopa_Shell_0"] = LoadTexture("resources/images/sprites/baddies/RedKoopaTroopa_Shell_0.png");

	textures["ParaKoopaBlue_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/ParaKoopaGreen_0.png");
	textures["ParaKoopaBlue_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/ParaKoopaGreen_1.png");
	textures["ParaKoopaBlue_LEFT_0"] = flipTexture(textures["ParaKoopaBlue_RIGHT_0"]);
	textures["ParaKoopaBlue_LEFT_1"] = flipTexture(textures["ParaKoopaBlue_RIGHT_1"]);
	textures["BlueKoopa_Shell_3"] = LoadTexture("resources/images/sprites/baddies/BlueKoopaTroopa_Shell_3.png");
	textures["BlueKoopa_Shell_2"] = LoadTexture("resources/images/sprites/baddies/BlueKoopaTroopa_Shell_2.png");
	textures["BlueKoopa_Shell_1"] = LoadTexture("resources/images/sprites/baddies/BlueKoopaTroopa_Shell_1.png");
	textures["BlueKoopa_Shell_0"] = LoadTexture("resources/images/sprites/baddies/BlueKoopaTroopa_Shell_0.png");

	textures["Bullet_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/BulletBill_0.png");
	textures["Bullet_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/BanzaiBill_0.png");
	textures["Bullet_LEFT_0"] = flipTexture(textures["Bullet_RIGHT_0"]);
	textures["Bullet_LEFT_1"] = flipTexture(textures["Bullet_RIGHT_1"]);
	textures["Bullet_Dead"] = LoadTexture("resources/images/sprites/baddies/Bullet_Dead.png");

	textures["PiranhaPlant_OPEN"] = LoadTexture("resources/images/sprites/baddies/PiranhaPlant_1.png");
	textures["PiranhaPlant_CLOSED"] = LoadTexture("resources/images/sprites/baddies/PiranhaPlant_0.png");
	textures["PiranhaPlant_Dead"] = LoadTexture("resources/images/sprites/baddies/PiranhaPlant_0.png");
	textures["PiranhaPlant_JUMPING"] = LoadTexture("resources/images/sprites/baddies/JumpingPiranhaPlant_0.png");
	textures["PiranhaPlant_JUMPING_1"] = LoadTexture("resources/images/sprites/baddies/JumpingPiranhaPlant_1.png");
	textures["PiranhaPlant_JUMPING_2"] = LoadTexture("resources/images/sprites/baddies/JumpingPiranhaPlant_2.png");
	textures["FirePiranhaPlant_OPEN"] = LoadTexture("resources/images/sprites/baddies/PiranhaPlant_1.png");
	textures["FirePiranhaPlant_CLOSED"] = LoadTexture("resources/images/sprites/baddies/PiranhaPlant_0.png");

	textures["EnemyFireball_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FlowerMarioFireball_0.png");
	textures["EnemyFireball_RIGHT_1"] = LoadTexture("resources/images/sprites/mario/FlowerMarioFireball_1.png");
	textures["EnemyFireball_RIGHT_2"] = LoadTexture("resources/images/sprites/mario/FlowerMarioFireball_2.png");
	textures["EnemyFireball_RIGHT_3"] = LoadTexture("resources/images/sprites/mario/FlowerMarioFireball_3.png");
	textures["EnemyFireball_LEFT_0"] = flipTexture(textures["FlowerMarioFireball_RIGHT_0"]);
	textures["EnemyFireball_LEFT_1"] = flipTexture(textures["FlowerMarioFireball_RIGHT_1"]);
	textures["EnemyFireball_LEFT_2"] = flipTexture(textures["FlowerMarioFireball_RIGHT_2"]);
	textures["EnemyFireball_LEFT_3"] = flipTexture(textures["FlowerMarioFireball_RIGHT_3"]);

	textures["Rex_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/Rex_2_0.png");
	textures["Rex_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/Rex_2_1.png");
	textures["Rex_LEFT_0"] = flipTexture(textures["Rex_RIGHT_0"]);
	textures["Rex_LEFT_1"] = flipTexture(textures["Rex_RIGHT_1"]);
	textures["Rex_Compressed_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/Rex_1_0.png");
	textures["Rex_Compressed_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/Rex_1_1.png");
	textures["Rex_Compressed_LEFT_0"] = flipTexture(textures["Rex_Compressed_RIGHT_0"]);
	textures["Rex_Compressed_LEFT_1"] = flipTexture(textures["Rex_Compressed_RIGHT_1"]);
	textures["Rex_Dead"] = LoadTexture("resources/images/sprites/baddies/Rex_Dead.png");

	textures["Muncher_0"] = LoadTexture("resources/images/sprites/baddies/Muncher_0.png");
	textures["Muncher_1"] = LoadTexture("resources/images/sprites/baddies/Muncher_1.png");

	textures["BobOmb_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/BobOmb_0.png");
	textures["BobOmb_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/BobOmb_1.png");
	textures["BobOmb_LEFT_0"] = flipTexture(textures["BobOmb_RIGHT_0"]);
	textures["BobOmb_LEFT_1"] = flipTexture(textures["BobOmb_RIGHT_1"]);
	textures["BobOmb_Activated_0"] = LoadTexture("resources/images/sprites/baddies/BobOmb_0.png");
	textures["BobOmb_Activated_1"] = LoadTexture("resources/images/sprites/baddies/BobOmb__1.png");
	textures["BobOmb_Explosion"] = LoadTexture("resources/images/sprites/baddies/Muncher_1.png");

	textures["DryBones_LEFT_0"] = LoadTexture("resources/images/sprites/baddies/DryBones_0.png");
	textures["DryBones_LEFT_1"] = LoadTexture("resources/images/sprites/baddies/DryBones_1.png");
	textures["DryBones_RIGHT_0"] = flipTexture(textures["DryBones_LEFT_0"]);
	textures["DryBones_RIGHT_1"] = flipTexture(textures["DryBones_LEFT_1"]);
	textures["DryBones_Collapse"] = LoadTexture("resources/images/sprites/baddies/DryBones_Collapse.png");

	textures["Spiny_LEFT_0"] = LoadTexture("resources/images/sprites/baddies/Spiny_LEFT_0.png");
	textures["Spiny_LEFT_1"] = LoadTexture("resources/images/sprites/baddies/Spiny_LEFT_1.png");
	textures["Spiny_RIGHT_0"] = flipTexture(textures["Spiny_LEFT_0"]);
	textures["Spiny_RIGHT_1"] = flipTexture(textures["Spiny_LEFT_1"]);
	textures["Spiny_DEAD"] = LoadTexture("resources/images/sprites/baddies/Spiny_DEAD.png");

	textures["BuzzyBeetle_LEFT_0"] = LoadTexture("resources/images/sprites/baddies/BuzzyBeetle_LEFT_0.png");
	textures["BuzzyBeetle_LEFT_1"] = LoadTexture("resources/images/sprites/baddies/BuzzyBeetle_LEFT_1.png");
	textures["BuzzyBeetle_RIGHT_0"] = flipTexture(textures["BuzzyBeetle_LEFT_0"]);
	textures["BuzzyBeetle_RIGHT_1"] = flipTexture(textures["BuzzyBeetle_LEFT_1"]);
	textures["BuzzyBeetle_Shell_2"] = LoadTexture("resources/images/sprites/baddies/BuzzyBeetle_Shell_2.png");
	textures["BuzzyBeetle_Shell_1"] = LoadTexture("resources/images/sprites/baddies/BuzzyBeetle_Shell_1.png");
	textures["BuzzyBeetle_Shell_0"] = LoadTexture("resources/images/sprites/baddies/BuzzyBeetle_Shell_0.png");
	// tile
	for (int i = 0; i <= 112; i++) {
		std::string path = "resources/images/tiles/AllTiles/tile_" + std::to_string(i) + ".png";
		textures["TILE_" + std::to_string(i)] = LoadTexture(path.c_str());
	}
	// background
	textures["BACKGROUND_1"] = LoadTexture("resources/images/backgrounds/background1.png");
}

void ResourceManager::loadSounds()
{
	sounds["PLAYER_JUMP"] = LoadSound("resources/sounds/smw_jump.wav");
	sounds["PLAYER_FIREBALL"] = LoadSound("resources/sounds/smw_fireball.wav");
	sounds["PLAYER_POWERUP"] = LoadSound("resources/sounds/smw_power-up.wav");
}

void ResourceManager::drawAllTiles() const
{
	const int tileSize = 32;
	const int tilesPerRow = 10;
	int i = 0;

	std::vector<std::pair<int, Texture2D>> sortedTiles;
	for (const auto& kv : textures)
	{
		const std::string& key = kv.first;

		if (key.find("TILE_") != 0)
			continue;

		// Extract numeric ID from key
		int id = std::stoi(key.substr(5));

		sortedTiles.emplace_back(id, kv.second);
	}

	// Sort by numeric ID
	std::sort(sortedTiles.begin(), sortedTiles.end(),
		[](const auto& a, const auto& b) {
			return a.first < b.first;
		});

	// Draw 
	for (const auto& pair : sortedTiles)
	{
		int id = pair.first;
		const Texture2D& tex = pair.second;

		int row = i / tilesPerRow;
		int col = i % tilesPerRow;

		int x = col * (tileSize + 16);
		int y = row * (tileSize + 24);

		if (tex.id != 0) {
			DrawTexture(tex, x, y, WHITE);
		}
		else {
			DrawRectangle(x, y, tileSize, tileSize, RED);
			DrawText("Missing", x + 2, y + tileSize / 2 - 5, 10, WHITE);
		}

		char label[32];
		snprintf(label, sizeof(label), "TILE_%d", id);
		DrawText(label, x, y + tileSize + 2, 10, DARKGRAY);

		i++;
	}
}

void ResourceManager::loadMusics()
{
	musics["MUSIC1"] = LoadMusicStream("resources/musics/music1.mp3");
}

void ResourceManager::unloadTextures() {
	for (auto const& [key, val] : textures) {
		unloadTexture(key);
	}
	textures.clear();
}
void ResourceManager::unloadSounds()
{
	for (auto const& [key, val] : sounds) {
		unloadSound(key);
	}
	sounds.clear();
}
void ResourceManager::unloadMusics()
{
	for (auto const& [key, val] : musics) {
		unloadMusic(key);
	}
	musics.clear();
}
void ResourceManager::unloadTexture(std::string key) {
	if (textures.find(key) != textures.end()) {
		UnloadTexture(textures[key]);
	}
}

void ResourceManager::unloadSound(std::string key)
{
	if (sounds.find(key) != sounds.end()) {
		UnloadSound(sounds[key]);
	}
}

void ResourceManager::unloadMusic(std::string key)
{
	if (musics.find(key) != musics.end()) {
		UnloadMusicStream(musics[key]);
	}
}

ResourceManager::~ResourceManager()
{
	UnloadAllResources();
}

void ResourceManager::LoadAllResources()
{
	loadTextures();
	loadSounds();
	loadMusics();
}

std::map<std::string, Texture2D>  ResourceManager::getTextures() {
	return textures;
}

std::map<std::string, Sound> ResourceManager::getSounds()
{
	return sounds;
}

std::map<std::string, Music> ResourceManager::getMusics()
{
	return musics;
}

Texture2D& ResourceManager::getTexture(const std::string& name)
{
	return textures[name];
}

Sound& ResourceManager::getSound(const std::string& name)
{
	return sounds[name];
}

Music& ResourceManager::getMusic(const std::string& name)
{
	return musics[name];
}

void ResourceManager::playMusic(const std::string& MusicName)
{
	if (currentMusic == MusicName) {
		UpdateMusicStream(getMusic(MusicName));
		return;
	}
	stopCurrentMusic();
	PlayMusicStream(getMusic(MusicName));
	currentMusic = MusicName;
}

bool ResourceManager::isMusicPlaying(const std::string& MusicName)
{
	return IsMusicStreamPlaying(getMusic(MusicName));
}

void ResourceManager::stopMusic(const std::string& MusicName)
{
	if (isMusicPlaying(MusicName))
		StopMusicStream(getMusic(MusicName));
}

void ResourceManager::stopCurrentMusic()
{
	if (!currentMusic.empty() && isMusicPlaying(currentMusic)) {
		StopMusicStream(getMusic(currentMusic));
		currentMusic.clear();
	}
}

void ResourceManager::playSound(const std::string& soundName)
{
	if (isPlayingSound(soundName) == false)
		PlaySound(getSound(soundName));
}

bool ResourceManager::isPlayingSound(const std::string& soundName)
{
	return IsSoundPlaying(getSound(soundName));
}

void ResourceManager::stopSound(const std::string& soundName)
{
	if (isPlayingSound(soundName))
		StopSound(getSound(soundName));
}

void ResourceManager::UnloadAllResources()
{
	unloadTextures();
	unloadSounds();
	unloadMusics();
}
Texture2D flipTexture(Texture2D& a) {
	Image img = LoadImageFromTexture(a);
	ImageFlipHorizontal(&img);
	Texture tex = LoadTextureFromImage(img);
	UnloadImage(img);
	return tex;
}