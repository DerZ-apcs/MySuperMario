#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <raylib.h>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

Texture2D flipTexture(Texture2D& a);

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
};
#endif