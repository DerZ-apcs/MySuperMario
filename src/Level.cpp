#include "../include/Level.h"

// Level implementation

Level::Level(const std::string& map, const std::string& background, const std::string& music, const std::string& name)
	: mapPath(map), backgroundName(background), musicName(music), MapName(name) {
}


std::string Level::getMapPath() const {
	return mapPath;
}

std::string Level::getBackGroundName() const {
	return backgroundName;
}

std::string Level::getName() const
{
	return MapName;
}

std::string Level::getMusic() const
{
	return musicName;
}

void Level::loadLevel(const json& j)
{
	mapPath = j["mapPath"]; // json file
	backgroundName = j["backgroundName"];
	musicName = j["musicName"];
	MapName = j["MapName"];
}

void Level::saveLevel(json& j) const
{
	j["mapPath"] = mapPath;
	j["backgroundName"] = backgroundName;
	j["musicName"] = musicName;
	j["MapName"] = MapName;
}
