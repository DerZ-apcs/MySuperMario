#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <raylib.h>
#include <map>
#include <string>
#include <vector>

Texture2D flipTexture(Texture2D& a);

class ResourceManager {
	template <class T>
	friend class Singleton;
private:
	ResourceManager() {}
	//~ResourceManager(){}
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	std::map<std::string, Texture2D> textures;
	std::map<std::string, Music> musics;
	std::map<std::string, Sound> sounds;

	mutable std::string currentMusic;
	void loadTextures();
	void loadSounds();
	void loadMusics();

	void unloadTextures();
	void unloadSounds();
	void unloadMusics();

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

	Texture2D& getTexture(const std::string& name);
	Sound& getSound(const std::string& name);
	Music& getMusic(const std::string& name);

	// play music track
	void playMusic(const std::string& MusicName);
	bool isMusicPlaying(const std::string& MusicName);
	void stopMusic(const std::string& MusicName);
	void stopCurrentMusic();

	// play sound effect
	void playSound(const std::string& soundName);
	bool isPlayingSound(const std::string& soundName);
	void stopSound(const std::string& soundName);
};
#endif