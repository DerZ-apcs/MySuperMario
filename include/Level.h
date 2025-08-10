#ifndef LEVEL_H
#define LEVEL_H

#include "../include/Map.h"
#include <string>

class Level {
private:
	std::string mapPath; // json file
	std::string backgroundName; 
	std::string musicName; 
	std::string MapName; // Map 1, 2, 3
public:
	Level(const std::string& map, const std::string& background, const std::string& music, const std::string& name);
	std::string getMapPath() const;
	std::string getBackGroundName() const;
	std::string getName() const;
	std::string getMusic() const;
	void loadLevel(const json& j);
	void saveLevel(json& j) const;
};
#endif