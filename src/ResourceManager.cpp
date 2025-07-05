#include "../include/ResourceManager.h"
#include <iostream>

void ResourceManager::loadTextures() {
	// BASE MARIO
	//textures["MARIO"] = LoadTexture("resources/images/sprites/mario/mario1.png");
	//cutSpriteSheetToTextures("MARIO", "resources/animation/mario1.txt");
	// Luigi
	textures["LUIGI"] = LoadTexture("resources/images/sprites/luigi/luigi1.png");
	cutSpriteSheetToTextures("LUIGI", "resources/animation/luigi1.txt");

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

	// dying
	textures["SmallMarioDying"] = LoadTexture("resources/images/sprites/mario/SmallMarioDying_0.png");

	// victory
	textures["SmallMarioVictory"] = LoadTexture("resources/images/sprites/mario/SmallMarioVictory_0.png");
	textures["SuperMarioVictory"] = LoadTexture("resources/images/sprites/mario/SuperMarioVictory_0.png");
	textures["FireMarioVictory"] = LoadTexture("resources/images/sprites/mario/FireMarioVictory.png");

	textures["luigi_victory"] = LoadTexture("resources/images/sprites/luigi/luigi_victory.png");
	textures["superluigi_victory"] = LoadTexture("resources/images/sprites/luigi/superluigi_victory.png");
	textures["fireluigi_victory"] = LoadTexture("resources/images/sprites/luigi/fireluigi_victory.png");

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
	//tile
	for (int i = 0; i <= 103; i++) {
		std::string path = "resources/images/tiles/AllTiles/tile_" + std::to_string(i) + ".png";
		textures["TILE_" + std::to_string(i)] = LoadTexture(path.c_str());
	}
	// background
	textures["BACKGROUND_1"] = LoadTexture("resources/images/backgrounds/background1.png");
	textures["BACKGROUND_2"] = LoadTexture("resources/images/backgrounds/background2.png");
	textures["MENU_SCREEN"] = LoadTexture("resources/images/backgrounds/Menuscreen.png");

	// GUI
	textures["HEART"] = LoadTexture("resources/images/backgrounds/heart.png");
	textures["COIN"] = LoadTexture("resources/images/backgrounds/coin.png");
	textures["BOARD"] = LoadTexture("resources/images/backgrounds/board.png");
	textures["MSIGN"] = LoadTexture("resources/images/backgrounds/multiplicationSign.png");
	textures["BOARD1"] = LoadTexture("resources/images/gui/board1.png");
	textures["BOARD2"] = LoadTexture("resources/images/gui/board2.png");
	textures["BOARD3"] = LoadTexture("resources/images/gui/board3.png");
	textures["LARGE_BOARD"] = LoadTexture("resources/images/gui/LargeBoard.png");
	textures["HOME_BUTTON"] = LoadTexture("resources/images/gui/home_button.png");
	textures["RESTART"] = LoadTexture("resources/images/gui/restart.png");
	textures["SETTING"] = LoadTexture("resources/images/gui/setting.png");
	textures["SOUND_OFF"] = LoadTexture("resources/images/gui/sound_off.png");
	textures["SOUND_ON"] = LoadTexture("resources/images/gui/sound_on.png");
}


void ResourceManager::loadFonts()
{
	fonts["Vogue"] = LoadFont("resources/Font/Vogue.ttf");
	fonts["HolenVintage"] = LoadFont("resources/Font/HolenVintage.otf");
	fonts["Sawer"] = LoadFont("resources/Font/Sawer.ttf");
	fonts["WinterMinie"] = LoadFont("resources/Font/WinterMinie.ttf");
	fonts["TimesNewRoman"] = LoadFont("resources/Font/TimesNewRoman.ttf");
}

void ResourceManager::loadSounds()
{
	sounds["PLAYER_JUMP"] = LoadSound("resources/sounds/smw_jump.wav");
	sounds["PLAYER_FIREBALL"] = LoadSound("resources/sounds/smw_fireball.wav");
	sounds["PLAYER_POWERUP"] = LoadSound("resources/sounds/smw_power-up.wav");
	sounds["enter_level.wav"] = LoadSound("resources/sounds/enter_level.wav");
	sounds["game_over.wav"] = LoadSound("resources/sounds/enter_level.wav");
	sounds["level_clear.wav"] = LoadSound("resources/sounds/level_clear.wav");
	sounds["lost_life.wav"] = LoadSound("resources/sounds/lost_life.wav");
	sounds["lost_suit.wav"] = LoadSound("resources/sounds/lost_suit.wav");
	sounds["pause.wav"] = LoadSound("resources/sounds/pause.wav");
	sounds["skid.wav"] = LoadSound("resources/sounds/skid.wav");
}

void ResourceManager::loadMusics()
{
	musics["TITLE"] = LoadMusicStream("resources/musics/Title.mp3");
	musics["MUSIC_1"] = LoadMusicStream("resources/musics/music1.mp3");
	musics["MUSIC_2"] = LoadMusicStream("resources/musics/music2.mp3");
	musics["COURSECLEAR"] = LoadMusicStream("resources/musics/courseClear.mp3");
}

void ResourceManager::unloadFonts()
{
	for (auto const& [key, val] : fonts) {
		unloadFont(key);
	}
	fonts.clear();
}

void ResourceManager::unloadTextures() {
	for (auto const &[key, val] : textures) {
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
void ResourceManager::unloadFont(std::string key)
{
	if (fonts.find(key) != fonts.end()) {
		UnloadFont(fonts[key]);
	}
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

void ResourceManager::cutSpriteSheetToTextures(const std::string& key, const std::string& filePath)
{
	if (textures.find(key) == textures.end()) {
		std::cerr << "ERROR texture not found" << key << std::endl;
		return;
	}
	Texture2D sheet = textures[key];
	Image sheetImage = LoadImageFromTexture(sheet); // Load full image

	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "ERROR Failed to open animation file: " << filePath << std::endl;
		return;
	}

	std::string line, animationName;
	int frameIndex = 0;
	while (getline(file, line)) {
		if (line.empty() || line[0] == '#') continue;
		if (line[0] == '$') {
			animationName = line.substr(1);
			frameIndex = 0;
		}
		else {
			std::istringstream iss(line);
			float x, y, width, height, duration, offsetX, offsetY, sizeX, sizeY;
			if (!(iss >> x >> y >> width >> height >> duration >> offsetX >> offsetY >> sizeX >> sizeY)) {
				std::cerr << "ERROR invalid frame data in: " << filePath << std::endl;
				continue;
			}
			Rectangle srcRect = { (float)x, (float)y, (float)width, (float)height };
			// Extract sub-image from sprite sheet
			Image frameImage = ImageFromImage(sheetImage, srcRect);

			// Convert to Texture2D and store it
			Texture2D frameTexture = LoadTextureFromImage(frameImage);
			UnloadImage(frameImage);

			std::string key = animationName + "_" + std::to_string(frameIndex++);
			textures[key] = frameTexture;
		}
	}
	UnloadImage(sheetImage);
	file.close();
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
	loadFonts();
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

std::map<std::string, Font> ResourceManager::getFonts()
{
	return std::map<std::string, Font>();
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

Font& ResourceManager::getFont(const std::string& name)
{
	return fonts[name];
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

std::string& ResourceManager::getCurrentMusic()
{
	std::string s = "";
	if (!currentMusic.empty() && isMusicPlaying(currentMusic))
		return currentMusic;
	else return s;
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
	unloadFonts();
}
Texture2D flipTexture(Texture2D& a) {
	Image img = LoadImageFromTexture(a);
	ImageFlipHorizontal(&img);
	Texture tex = LoadTextureFromImage(img);
	UnloadImage(img);
	return tex;
}