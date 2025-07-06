#include "../include/ResourceManager.h"
#include <iostream>

void ResourceManager::loadTextures() {
	// move //
	
	// small mario
	textures["SmallMario_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/SmallMario_0.png");
	textures["SmallMario_RIGHT_1"] = LoadTexture("resources/images/sprites/mario/SmallMario_1.png");
	textures["SmallMario_LEFT_0"] = flipTexture(textures["SmallMario_RIGHT_0"]);
	textures["SmallMario_LEFT_1"] = flipTexture(textures["SmallMario_RIGHT_1"]);

	// super mario
	textures["SuperMario_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/SuperMario_0.png");
	textures["SuperMario_RIGHT_1"] = LoadTexture("resources/images/sprites/mario/SuperMario_1.png");
	textures["SuperMario_RIGHT_2"] = LoadTexture("resources/images/sprites/mario/SuperMario_2.png");
	textures["SuperMario_LEFT_0"] = flipTexture(textures["SuperMario_RIGHT_0"]);
	textures["SuperMario_LEFT_1"] = flipTexture(textures["SuperMario_RIGHT_1"]);
	textures["SuperMario_LEFT_2"] = flipTexture(textures["SuperMario_RIGHT_2"]);

	// FireMario
	textures["FireMario_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FireMario_0.png");
	textures["FireMario_RIGHT_1"] = LoadTexture("resources/images/sprites/mario/FireMario_1.png");
	textures["FireMario_RIGHT_2"] = LoadTexture("resources/images/sprites/mario/FireMario_2.png");
	textures["FireMario_LEFT_0"] = flipTexture(textures["FireMario_RIGHT_0"]);
	textures["FireMario_LEFT_1"] = flipTexture(textures["FireMario_RIGHT_1"]);
	textures["FireMario_LEFT_2"] = flipTexture(textures["FireMario_RIGHT_2"]);

	// jump 
	textures["SmallMarioJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/SmallMarioJumping_0.png");
	textures["SmallMarioJumping_LEFT_0"] = flipTexture(textures["SmallMarioJumping_RIGHT_0"]);
	textures["SuperMarioJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/SuperMarioJumping_0.png");
	textures["SuperMarioJumping_LEFT_0"] = flipTexture(textures["SuperMarioJumping_RIGHT_0"]);

	// fall
		// mario
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
	textures["SuperMarioDying"] = textures["SmallMarioDying"];
	textures["FireMarioDying"] = LoadTexture("resources/images/sprites/mario/FireMarioDying_0.png");

	// victory
	textures["SmallMarioVictory"] = LoadTexture("resources/images/sprites/mario/SmallMarioVictory_0.png");
	textures["SuperMarioVictory"] = LoadTexture("resources/images/sprites/mario/SuperMarioVictory_0.png");
	textures["FireMarioVictory"] = LoadTexture("resources/images/sprites/mario/FireMarioVictory.png");
		
	// trasition

	textures["TransitioningMario_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/TransitioningMario_1.png");
	textures["TransitioningMario_LEFT_0"] = flipTexture(textures["TransitioningMario_RIGHT_0"]);
	textures["TransitioningFireMario_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/TransitioningFireMario.png");
	textures["TransitioningFireMario_LEFT_0"] = flipTexture(textures["TransitioningFireMario_RIGHT_0"]);
	// fire mario 

	textures["FireMarioJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FireMarioJumping_0.png");
	textures["FireMarioJumping_LEFT_0"] = flipTexture(textures["FireMarioJumping_RIGHT_0"]);

	textures["FireMarioFalling_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FireMarioFalling_0.png");
	textures["FireMarioFalling_LEFT_0"] = flipTexture(textures["FireMarioFalling_RIGHT_0"]);

	textures["FireMarioDucking_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FireMario_Ducking_0.png");
	textures["FireMarioDucking_LEFT_0"] = flipTexture(textures["FireMarioDucking_RIGHT_0"]);

	textures["FireMarioThrowingFireball_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FireMario_Firing_0.png");
	textures["FireMarioThrowingFireball_LEFT_0"] = flipTexture(textures["FireMarioThrowingFireball_RIGHT_0"]);

	// star state for mario & luigi (small, super, fire)
	generateStarMarioVariants(); // for star mario
	generateLuigiVariants(); // generate all textures of luigi

	// fireball
	textures["FlowerMarioFireball_RIGHT_0"] = LoadTexture("resources/images/sprites/mario/FlowerMarioFireball_0.png");
	textures["FlowerMarioFireball_RIGHT_1"] = LoadTexture("resources/images/sprites/mario/FlowerMarioFireball_1.png");
	textures["FlowerMarioFireball_RIGHT_2"] = LoadTexture("resources/images/sprites/mario/FlowerMarioFireball_2.png");
	textures["FlowerMarioFireball_RIGHT_3"] = LoadTexture("resources/images/sprites/mario/FlowerMarioFireball_3.png");
	textures["FlowerMarioFireball_LEFT_0"] = flipTexture(textures["FlowerMarioFireball_RIGHT_0"]);
	textures["FlowerMarioFireball_LEFT_1"] = flipTexture(textures["FlowerMarioFireball_RIGHT_1"]);
	textures["FlowerMarioFireball_LEFT_2"] = flipTexture(textures["FlowerMarioFireball_RIGHT_2"]);
	textures["FlowerMarioFireball_LEFT_3"] = flipTexture(textures["FlowerMarioFireball_RIGHT_3"]);

	//tile
	for (int i = 0; i <= 103; i++) {
		std::string path = "resources/images/tiles/AllTiles/tile_" + std::to_string(i) + ".png";
		textures["TILE_" + std::to_string(i)] = LoadTexture(path.c_str());
	}
	// background
	textures["BACKGROUND_1"] = LoadTexture("resources/images/backgrounds/background1.png");
	textures["BACKGROUND_2"] = LoadTexture("resources/images/backgrounds/background2.png");
	textures["BACKGROUND_3"] = LoadTexture("resources/images/backgrounds/background3.png");
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
	/*fonts["Vogue"] = LoadFont("resources/Font/Vogue.ttf");
	fonts["HolenVintage"] = LoadFont("resources/Font/HolenVintage.otf");
	fonts["Sawer"] = LoadFont("resources/Font/Sawer.ttf");
	fonts["WinterMinie"] = LoadFont("resources/Font/WinterMinie.ttf");
	fonts["TimesNewRoman"] = LoadFont("resources/Font/TimesNewRoman.ttf");*/
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
	musics["MUSIC_3"] = LoadMusicStream("resources/musics/music2.mp3");
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

void ResourceManager::generateStarMarioVariants()
{
	for (const auto& [key, tex] : textures) {
		if (key.find("Mario") != std::string::npos &&
			key.find("Star") == std::string::npos) {
			
			Texture2D star = ConvertMarioToStarMario(tex);
			std::string starKey = "Star" + key;
			textures[starKey] = star;
		}
	}
}

void ResourceManager::generateStarLuigiVariants()
{
	for (const auto& [key, tex] : textures) {
		// skip non-mario or already star textures
		if (key.find("Mario") == std::string::npos || key.find("Star") != std::string::npos)
			continue;
		// Extract Mario type from key (e.g. "SmallMario", "FireMario", etc.)
		size_t marioPos = key.find("Mario");
		std::string marioType = key.substr(0, marioPos); // eg. "Small", "Super", "Fire_"
		std::string suffix = key.substr(marioPos + 5); // after "Mario"

		// Build Luigi key
		std::string starLuigiKey = "Star" + marioType + "Luigi" + suffix;

		// ---- Case 1: Small or Super Mario → reuse Star Mario directly
		if (marioType == "Small" || marioType == "Super") {
			std::string starMarioKey = "Star" + key;
			if (textures.count(starMarioKey)) {
				textures[starLuigiKey] = textures[starMarioKey]; // Share texture
			}
		}

		// ---- Case 2: Fire Mario → use special conversion
		else if (marioType == "Fire") {
			Texture2D starLuigi = ConvertFireStarMarioToFireStarLuigi(tex);
			textures[starLuigiKey] = starLuigi;
		}
	}
}

void ResourceManager::generateLuigiVariants()
{
	for (const auto& [key, tex] : textures) {
		if (key.find("Mario") == std::string::npos || key.find("Luigi") != std::string::npos) continue; // skip non-mario or already luigi

		size_t marioPos = key.find("Mario");
		std::string CState = key.substr(0, marioPos);
		std::string suffix = key.substr(marioPos + 5);

		std::string LuigiKey = CState + "Luigi" + suffix;
		// Case 1: normal & super mario convert to luigi
		if (CState == "Small" || CState == "Super" || CState == "Transitioning")
			loadLuigiFromMario(key, LuigiKey, ConvertMarioToLuigi);
		// Case 2: fire mario convert to luigi
		else if (CState == "Fire" || CState == "TransitioningFire")
			loadLuigiFromMario(key, LuigiKey, ConvertFireMarioToFireLuigi);
	}
	generateStarLuigiVariants();
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

void ResourceManager::loadLuigiFromMario(const std::string& marioKey, const std::string& luigiKey, Texture2D(*converter)(Texture2D))
{
	Texture2D marioTex = textures[marioKey];
	textures[luigiKey] = converter(marioTex);
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

// Check approximate match with a threshold
bool ResourceManager::IsColorNear(Color c, Color target, int tolerance) {
	int dr = c.r - target.r;
	int dg = c.g - target.g;
	int db = c.b - target.b;
	return (dr * dr + dg * dg + db * db) <= (tolerance * tolerance);
}

Texture2D ResourceManager::ConvertMarioToStarMario(Texture2D marioTexture)
{
	Image image = LoadImageFromTexture(marioTexture);
	Color* pixels = LoadImageColors(image);
	int count = image.width * image.height;

	for (int i = 0; i < count; i++) {
		Color& c = pixels[i];

		if (c.a == 0) continue; // skip transparent

		if (IsColorNear(c, MARIO_RED)) {
			c = Color{ 255, 255, 0, 255 };
		}
		else if (IsColorNear(c, MARIO_RED_DARK)) {
			c = Color{ 255, 204, 0, 255 };
		}
		// Outlines → white
		else if (
			IsColorNear(c, Color{ 0, 0, 0 }) ||               // black
			IsColorNear(c, Color{ 80, 0, 0 }) ||              // dark brown/red
			IsColorNear(c, Color{ 136, 88, 24 }) ||           // dark yellow
			IsColorNear(c, Color{ 32, 48, 136 })              // dark blue
			) {
			c = Color{ 255, 255, 255, 255 }; // turn to white
		}
	}

	MemFree(image.data);
	image.data = pixels;

	Texture2D starTex = LoadTextureFromImage(image);
	UnloadImage(image);
	return starTex;
}

Texture2D ResourceManager::ConvertFireStarMarioToFireStarLuigi(Texture2D marioTexture)
{
	Texture2D fireStarMario = ConvertMarioToStarMario(marioTexture);
	Texture2D fireStarLuigi = ConvertFireMarioToFireLuigi(fireStarMario);
	UnloadTexture(fireStarMario); // optional
	return fireStarLuigi;
}

Texture2D ResourceManager::ConvertFireMarioToFireLuigi(Texture2D marioTexture) {
	Image image = LoadImageFromTexture(marioTexture);
	Color* pixels = LoadImageColors(image);
	int count = image.width * image.height;

	for (int i = 0; i < count; i++) {
		if (IsColorNear(pixels[i], FIRE_RED)) {
			pixels[i] = LUIGI_GREEN;
		}
		else if (IsColorNear(pixels[i], FIRE_RED_DARK)) {
			pixels[i] = LUIGI_GREEN_DARK;
		}
	}

	MemFree(image.data);
	image.data = pixels;

	Texture2D luigiTexture = LoadTextureFromImage(image);
	UnloadImage(image);
	return luigiTexture;
}

Texture2D ResourceManager::ConvertMarioToLuigi(Texture2D marioTexture) {
	Image image = LoadImageFromTexture(marioTexture);
	Color* pixels = LoadImageColors(image);
	int count = image.width * image.height;

	for (int i = 0; i < count; i++) {
		if (IsColorNear(pixels[i], MARIO_RED)) {
			pixels[i] = LUIGI_GREEN;
		}
		else if (IsColorNear(pixels[i], MARIO_RED_DARK)) {
			pixels[i] = LUIGI_GREEN_DARK;
		}
	}

	MemFree(image.data); // Free original data
	image.data = pixels;

	Texture2D luigiTexture = LoadTextureFromImage(image);
	UnloadImage(image);
	return luigiTexture;
}

Color ResourceManager::getRainbowTint(float time) {
	unsigned char r = (unsigned char)(128 + 127 * sinf(time * 2));
	unsigned char g = (unsigned char)(128 + 127 * sinf(time * 2 + 2));
	unsigned char b = (unsigned char)(128 + 127 * sinf(time * 2 + 4));
	return Color { r, g, b, 255 };
}

