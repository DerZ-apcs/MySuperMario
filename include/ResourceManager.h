#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <raylib.h>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

Texture2D flipTexture(Texture2D& a);

const Color MARIO_RED = { 248, 64, 112, 255 };  // Main red
const Color MARIO_RED_DARK = { 176, 40, 96, 255 };   // Shadow red
// Corresponding greens for Luigi
const Color LUIGI_GREEN = { 80, 192, 56, 255 };  // Light green
const Color LUIGI_GREEN_DARK = { 64, 128, 48, 255 };  // Darker green
// FIRE MARIO Colors
const Color FIRE_RED = { 248, 0, 0, 255 };
const Color FIRE_RED_DARK = { 184, 0, 0, 255 };

class ResourceManager {
	template <class T>
	friend class Singleton;
private:
	ResourceManager(){}
	//~ResourceManager(){}
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	std::map<std::string, Texture2D> textures;
	std::map<std::string, Music> musics;
	std::map<std::string, Sound> sounds;
	std::map<std::string, Font> fonts;

	mutable std::string currentMusic;
	void loadFonts();
	void loadTextures();
	void loadSounds();
	void loadMusics();

	void unloadFonts();
	void unloadTextures();
	void unloadSounds();
	void unloadMusics();

	void unloadFont(std::string key);
	void unloadTexture(std::string key);
	void unloadSound(std::string key);
	void unloadMusic(std::string key);
	
	void cutSpriteSheetToTextures(const std::string& key, const std::string& filePath);
public:
	~ResourceManager();
	void LoadAllResources();
	void UnloadAllResources();

	std::map<std::string, Texture2D> getTextures();
	std::map<std::string, Sound> getSounds();
	std::map<std::string, Music> getMusics();
	std::map<std::string, Font> getFonts();

	Texture2D& getTexture(const std::string& name);
	Sound& getSound(const std::string& name);
	Music& getMusic(const std::string& name);
	Font& getFont(const std::string& name);

	// play music track
	void playMusic(const std::string& MusicName);
	bool isMusicPlaying(const std::string& MusicName);
	void stopMusic(const std::string& MusicName);
	void stopCurrentMusic();
	std::string& getCurrentMusic();

	// play sound effect
	void playSound(const std::string& soundName);
	bool isPlayingSound(const std::string& soundName);
	void stopSound(const std::string& soundName);

	void loadLuigiFromMario(const std::string& marioKey, const std::string& luigiKey, Texture2D(*converter)(Texture2D));
	static Texture2D ConvertFireMarioToFireLuigi(Texture2D marioTexture);
	static Texture2D ConvertMarioToLuigi(Texture2D marioTexture);
	static bool IsColorNear(Color c, Color target, int tolerance = 20);
};
#endif