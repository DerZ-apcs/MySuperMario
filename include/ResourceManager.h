#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <raylib.h>
#include <map>
#include <string>
#include <vector>

Texture2D flipTexture(Texture2D& a);

class ResourceManager {
private:
	static std::map<std::string, Texture2D> textures;
public:
	static void loadTextures();
	static void unloadTextures();
	static void unloadTexture(std::string key);
	static void LoadAllResources();

	static std::map<std::string, Texture2D> getTextures();
	static Texture2D& getTexture(const std::string name);
	static void UnloadAllResources();
};
#endif