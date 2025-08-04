#include <raylib.h>
#include "../include/Game.h"
#include "../include/GameSerialization.h"
#include <fstream>
using namespace std;

//int main() {
//	Game game;
//	game.init();
//
//	return 0;
//}

void loadPlayersFromFile(const std::string& filename, std::vector<std::unique_ptr<Character>>& multiplayers);
int main() {
	std::vector<std::unique_ptr<Character>> test;
	/*auto mario = std::make_unique<Mario>();
	mario->setPosition({ 100, 200 });
	mario->setVel({ 50, 0 });
	mario->setLives(3);
	mario->setScores(1500);
	mario->setCoins(25);
	mario->setPhase(DEFAULT_PHASE);
	mario->setState(EntityState::ON_GROUND);
	mario->setCharacterState(CharacterState::STATE_SMALL);

	auto luigi = std::make_unique<Luigi>();
	luigi->setPosition({ 500, 200 });
	luigi->setVel({ 50, 50 });
	luigi->setLives(4);
	luigi->setScores(1000);
	luigi->setCoins(20);
	luigi->setPhase(DEFAULT_PHASE);
	luigi->setState(EntityState::FALLING);
	luigi->setCharacterState(CharacterState::STATE_FIRE);

	test.push_back(std::move(mario));
	test.push_back(std::move(luigi));


	json savedata;
	saveMultiCharacters(test, savedata);
	std::ofstream fout("save_test.json");
	fout << savedata.dump(4); 
	fout.close();
	std::cout << "Characters saved to save_test.json\n";*/

	// load from json file

	std::vector<std::unique_ptr<Character>> loadedPlayers;
	loadPlayersFromFile("save_test.json", loadedPlayers);
	for (auto& p : loadedPlayers) {
		std::cout << "Loaded player at pos: " << p->getPosition().x << ", " << p->getPosition().y << "\n";
	}
	return 0;
}

void loadPlayersFromFile(const std::string& filename, std::vector<std::unique_ptr<Character>>& multiplayers) {
	std::ifstream fin(filename);
	if (!fin) {
		std::cerr << "Failed to open save files: " << filename << "\n";
		return;
	}
	nlohmann::json jsonData;
	fin >> jsonData;
	for (const auto& player : jsonData["players"]) {
		multiplayers.push_back(loadCharacter(player));
	}
	std::cout << "Loaded" << multiplayers.size() << " players from " << filename << "\n";
}
