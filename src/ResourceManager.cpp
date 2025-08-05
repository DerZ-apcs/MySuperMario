#include "../include/ResourceManager.h"
#include <iostream>

void ResourceManager::loadTextures() {
	// move //
	
	// small mario
		// for choosing character
	textures["SmallMario_Straight"] = LoadTexture("resources/images/sprites/mario/SmallMario_Straight_0.png");

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


	// Peach
		// for choosing character
	textures["SmallPeach_Straight"] = LoadTexture("resources/images/sprites/peach/SmallPeach_Dying.png");

	textures["SmallPeach_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/SmallPeach_0.png");
	textures["SmallPeach_LEFT_0"] = flipTexture(textures["SmallPeach_RIGHT_0"]);
	textures["SmallPeach_RIGHT_1"] = LoadTexture("resources/images/sprites/peach/SmallPeach_1.png");
	textures["SmallPeach_LEFT_1"] = flipTexture(textures["SmallPeach_RIGHT_1"]);
	textures["SmallPeach_RIGHT_2"] = LoadTexture("resources/images/sprites/peach/SmallPeach_2.png");
	textures["SmallPeach_LEFT_2"] = flipTexture(textures["SmallPeach_RIGHT_2"]);

	textures["SmallPeachDying"] = LoadTexture("resources/images/sprites/peach/SmallPeach_Dying.png");
	textures["SmallPeachJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/SmallPeach_Jumping.png");
	textures["SmallPeachJumping_LEFT_0"] = flipTexture(textures["SmallPeachJumping_RIGHT_0"]);
	textures["SmallPeachDucking_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/SmallPeachDucking.png");
	textures["SmallPeachDucking_LEFT_0"] = flipTexture(textures["SmallPeachDucking_RIGHT_0"]);

	textures["SmallPeachFalling_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/SmallPeach_Jumping.png");
	textures["SmallPeachFalling_LEFT_0"] = flipTexture(textures["SmallPeachFalling_RIGHT_0"]);
	textures["SmallPeachVictory"] = LoadTexture("resources/images/sprites/peach/SmallPeach_Victory.png");

	// super peach
	textures["SuperPeach_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/SuperPeach_0.png");
	textures["SuperPeach_LEFT_0"] = flipTexture(textures["SuperPeach_RIGHT_0"]);
	textures["SuperPeach_RIGHT_1"] = LoadTexture("resources/images/sprites/peach/SuperPeach_1.png");
	textures["SuperPeach_LEFT_1"] = flipTexture(textures["SuperPeach_RIGHT_1"]);
	textures["SuperPeach_RIGHT_2"] = LoadTexture("resources/images/sprites/peach/SuperPeach_2.png");
	textures["SuperPeach_LEFT_2"] = flipTexture(textures["SuperPeach_RIGHT_2"]);

	textures["SuperPeachDying"] = LoadTexture("resources/images/sprites/peach/SuperPeachDying.png");
	textures["SuperPeachJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/SuperPeachJumping.png");
	textures["SuperPeachJumping_LEFT_0"] = flipTexture(textures["SuperPeachJumping_RIGHT_0"]);
	textures["SuperPeachDucking_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/SuperPeachDucking.png");
	textures["SuperPeachDucking_LEFT_0"] = flipTexture(textures["SuperPeachDucking_RIGHT_0"]);

	textures["SuperPeachFalling_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/SuperPeachFalling.png");
	textures["SuperPeachFalling_LEFT_0"] = flipTexture(textures["SuperPeachFalling_RIGHT_0"]);

	textures["SuperPeachVictory"] = LoadTexture("resources/images/sprites/peach/SuperPeachVictory.png");
	// Fire Peach
	textures["FirePeach_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/FirePeach_0.png");
	textures["FirePeach_LEFT_0"] = flipTexture(textures["FirePeach_RIGHT_0"]);
	textures["FirePeach_RIGHT_1"] = LoadTexture("resources/images/sprites/peach/FirePeach_1.png");
	textures["FirePeach_LEFT_1"] = flipTexture(textures["FirePeach_RIGHT_1"]);
	textures["FirePeach_RIGHT_2"] = LoadTexture("resources/images/sprites/peach/FirePeach_2.png");
	textures["FirePeach_LEFT_2"] = flipTexture(textures["FirePeach_RIGHT_2"]);

	textures["FirePeachDying"] = LoadTexture("resources/images/sprites/peach/FirePeach_Dying.png");
	textures["FirePeachJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/FirePeachJumping.png");
	textures["FirePeachJumping_LEFT_0"] = flipTexture(textures["FirePeachJumping_RIGHT_0"]);
	textures["FirePeachDucking_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/FirePeachDucking.png");
	textures["FirePeachDucking_LEFT_0"] = flipTexture(textures["FirePeachDucking_RIGHT_0"]);

	textures["FirePeachFalling_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/FirePeachFalling.png");
	textures["FirePeachFalling_LEFT_0"] = flipTexture(textures["FirePeachFalling_RIGHT_0"]);

	textures["FirePeachVictory"] = LoadTexture("resources/images/sprites/peach/FirePeach_Victory.png");

	textures["FirePeachThrowingFireball_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/FirePeachFiring_0.png");
	textures["FirePeachThrowingFireball_LEFT_0"] = flipTexture(textures["FireMarioThrowingFireball_RIGHT_0"]);

		// transitioning
		textures["TransitioningPeach_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/SuperPeach_0.png");
		textures["TransitioningPeach_LEFT_0"] = flipTexture(textures["TransitioningPeach_RIGHT_0"]);
		textures["TransitioningFirePeach_RIGHT_0"] = LoadTexture("resources/images/sprites/peach/FirePeach_0.png");
		textures["TransitioningFirePeach_LEFT_0"] = flipTexture(textures["TransitioningFirePeach_RIGHT_0"]);
	// Marisa
		// for choosing character
	textures["SmallMarisa_Straight"] = LoadTexture("resources/images/sprites/megaman/SmallMarisa_Dying.png");
		// Marisa
	textures["SmallMarisa_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/SmallMarisa_0.png");
	textures["SmallMarisa_LEFT_0"] = flipTexture(textures["SmallMarisa_RIGHT_0"]);
	textures["SmallMarisa_RIGHT_1"] = LoadTexture("resources/images/sprites/megaman/SmallMarisa_1.png");
	textures["SmallMarisa_LEFT_1"] = flipTexture(textures["SmallMarisa_RIGHT_1"]);
	textures["SmallMarisa_RIGHT_2"] = LoadTexture("resources/images/sprites/megaman/SmallMarisa_2.png");
	textures["SmallMarisa_LEFT_2"] = flipTexture(textures["SmallMarisa_RIGHT_2"]);

	textures["SmallMarisaDying"] = LoadTexture("resources/images/sprites/megaman/SmallMarisa_Dying.png");
	textures["SmallMarisaJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/SmallMarisa_Falling.png");
	textures["SmallMarisaJumping_LEFT_0"] = flipTexture(textures["SmallMarisaJumping_RIGHT_0"]);
	textures["SmallMarisaDucking_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/SmallMarisa_Ducking.png");
	textures["SmallMarisaDucking_LEFT_0"] = flipTexture(textures["SmallMarisaDucking_RIGHT_0"]);

	textures["SmallMarisaFalling_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/SmallMarisa_Falling.png");
	textures["SmallMarisaFalling_LEFT_0"] = flipTexture(textures["SmallMarisaFalling_RIGHT_0"]);

	textures["SmallMarisaVictory"] = LoadTexture("resources/images/sprites/megaman/SmallMarisa_Victory.png");

	// Super Marisa
	textures["SuperMarisa_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/SuperMarisa_0.png");
	textures["SuperMarisa_LEFT_0"] = flipTexture(textures["SuperMarisa_RIGHT_0"]);
	textures["SuperMarisa_RIGHT_1"] = LoadTexture("resources/images/sprites/megaman/SuperMarisa_1.png");
	textures["SuperMarisa_LEFT_1"] = flipTexture(textures["SuperMarisa_RIGHT_1"]);
	textures["SuperMarisa_RIGHT_2"] = LoadTexture("resources/images/sprites/megaman/SuperMarisa_2.png");
	textures["SuperMarisa_LEFT_2"] = flipTexture(textures["SuperMarisa_RIGHT_2"]);

	textures["SuperMarisaDying"] = LoadTexture("resources/images/sprites/megaman/SuperMarisa_Dying.png");
	textures["SuperMarisaJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/SuperMarisa_Falling.png");
	textures["SuperMarisaJumping_LEFT_0"] = flipTexture(textures["SuperMarisaJumping_RIGHT_0"]);
	textures["SuperMarisaDucking_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/SuperMarisa_Ducking.png");
	textures["SuperMarisaDucking_LEFT_0"] = flipTexture(textures["SuperMarisaDucking_RIGHT_0"]);

	textures["SuperMarisaFalling_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/SuperMarisa_Falling.png");
	textures["SuperMarisaFalling_LEFT_0"] = flipTexture(textures["SuperMarisaFalling_RIGHT_0"]);

	textures["SuperMarisaVictory"] = LoadTexture("resources/images/sprites/megaman/SuperMarisa_Victory.png");

	// Fire Marisa
	textures["FireMarisa_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/FireMarisa_0.png");
	textures["FireMarisa_LEFT_0"] = flipTexture(textures["FireMarisa_RIGHT_0"]);
	textures["FireMarisa_RIGHT_1"] = LoadTexture("resources/images/sprites/megaman/FireMarisa_1.png");
	textures["FireMarisa_LEFT_1"] = flipTexture(textures["FireMarisa_RIGHT_1"]);
	textures["FireMarisa_RIGHT_2"] = LoadTexture("resources/images/sprites/megaman/FireMarisa_2.png");
	textures["FireMarisa_LEFT_2"] = flipTexture(textures["FireMarisa_RIGHT_2"]);

	textures["FireMarisaDying"] = LoadTexture("resources/images/sprites/megaman/FireMarisa_Dying.png");
	textures["FireMarisaJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/FireMarisa_Falling.png");
	textures["FireMarisaJumping_LEFT_0"] = flipTexture(textures["FireMarisaJumping_RIGHT_0"]);
	textures["FireMarisaDucking_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/FireMarisa_Ducking.png");
	textures["FireMarisaDucking_LEFT_0"] = flipTexture(textures["FireMarisaDucking_RIGHT_0"]);

	textures["FireMarisaFalling_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/FireMarisa_Falling.png");
	textures["FireMarisaFalling_LEFT_0"] = flipTexture(textures["FireMarisaFalling_RIGHT_0"]);

	textures["FireMarisaVictory"] = LoadTexture("resources/images/sprites/megaman/FireMarisa_Victory.png");

	textures["FireMarisaThrowingFireball_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/FireMarisa_Firing.png");
	textures["FireMarisaThrowingFireball_LEFT_0"] = flipTexture(textures["FireMarisaThrowingFireball_RIGHT_0"]);
		// transitioning
				// transitioning
	textures["TransitioningMarisa_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/SuperMarisa_0.png");
	textures["TransitioningMarisa_LEFT_0"] = flipTexture(textures["TransitioningMarisa_RIGHT_0"]);
	textures["TransitioningFireMarisa_RIGHT_0"] = LoadTexture("resources/images/sprites/megaman/FireMarisa_0.png");
	textures["TransitioningFireMarisa_LEFT_0"] = flipTexture(textures["TransitioningFireMarisa_RIGHT_0"]);

	// Toad
	textures["SmallToad_Straight"] = LoadTexture("resources/images/sprites/toad/SmallToad_Straight.png");
	textures["SmallToad_RIGHT_0"] = LoadTexture("resources/images/sprites/toad/SmallToad_0.png");
	textures["SmallToad_RIGHT_1"] = LoadTexture("resources/images/sprites/toad/SmallToad_1.png");
	textures["SmallToad_LEFT_0"] = flipTexture(textures["SmallToad_RIGHT_0"]);
	textures["SmallToad_LEFT_1"] = flipTexture(textures["SmallToad_RIGHT_1"]);

	textures["SmallToadJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/toad/SmallToad_Jumping.png");
	textures["SmallToadJumping_LEFT_0"] = flipTexture(textures["SmallToadJumping_RIGHT_0"]);
	textures["SmallToadFalling_RIGHT_0"] = LoadTexture("resources/images/sprites/toad/SmallToad_Falling.png");
	textures["SmallToadFalling_LEFT_0"] = flipTexture(textures["SmallToadFalling_RIGHT_0"]);
	textures["SmallToadDucking_RIGHT_0"] = LoadTexture("resources/images/sprites/toad/SmallToad_Ducking.png");
	textures["SmallToadDucking_LEFT_0"] = flipTexture(textures["SmallToadDucking_RIGHT_0"]);
	textures["SmallToadDying"] = LoadTexture("resources/images/sprites/toad/SmallToad_Dying.png");
		// super toad
	textures["SuperToad_RIGHT_0"] = LoadTexture("resources/images/sprites/toad/SuperToad_0.png");
	textures["SuperToad_LEFT_0"] = flipTexture(textures["SuperToad_RIGHT_0"]);
	textures["SuperToad_RIGHT_1"] = LoadTexture("resources/images/sprites/toad/SuperToad_1.png");
	textures["SuperToad_LEFT_1"] = flipTexture(textures["SuperToad_RIGHT_1"]);
	textures["SuperToad_RIGHT_2"] = LoadTexture("resources/images/sprites/toad/SuperToad_2.png");
	textures["SuperToad_LEFT_2"] = flipTexture(textures["SuperToad_RIGHT_2"]);

	textures["SuperToadJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/toad/SuperToad_jumpingfalling.png");
	textures["SuperToadJumping_LEFT_0"] = flipTexture(textures["SuperToadJumping_RIGHT_0"]);
	textures["SuperToadFalling_RIGHT_0"] = textures["SuperToadJumping_RIGHT_0"];
	textures["SuperToadFalling_LEFT_0"] = flipTexture(textures["SuperToadFalling_RIGHT_0"]);
	textures["SuperToadDucking_RIGHT_0"] = LoadTexture("resources/images/sprites/toad/SuperToad_Ducking.png");
	textures["SuperToadDucking_LEFT_0"] = flipTexture(textures["SuperToadDucking_RIGHT_0"]);
	textures["SuperToadDying"] = textures["SmallToadDying"];
		// fire toad
	textures["FireToad_RIGHT_0"] = LoadTexture("resources/images/sprites/toad/FireToad_0.png");
	textures["FireToad_LEFT_0"] = flipTexture(textures["FireToad_RIGHT_0"]);
	textures["FireToad_RIGHT_1"] = LoadTexture("resources/images/sprites/toad/FireToad_1.png");
	textures["FireToad_LEFT_1"] = flipTexture(textures["FireToad_RIGHT_1"]);
	textures["FireToad_RIGHT_2"] = LoadTexture("resources/images/sprites/toad/FireToad_2.png");
	textures["FireToad_LEFT_2"] = flipTexture(textures["FireToad_RIGHT_2"]);

	textures["FireToadJumping_RIGHT_0"] = LoadTexture("resources/images/sprites/toad/FireToad_JumpingFalling.png");
	textures["FireToadJumping_LEFT_0"] = flipTexture(textures["FireToadJumping_RIGHT_0"]);
	textures["FireToadFalling_RIGHT_0"] = textures["FireToadJumping_RIGHT_0"];
	textures["FireToadFalling_LEFT_0"] = flipTexture(textures["FireToadFalling_RIGHT_0"]);
	textures["FireToadDucking_RIGHT_0"] = LoadTexture("resources/images/sprites/toad/FireToad_Ducking.png");
	textures["FireToadDucking_LEFT_0"] = flipTexture(textures["FireToadDucking_RIGHT_0"]);
	textures["FireToadDying"] = textures["SmallToadDying"];
	textures["FireToadThrowingFireball_RIGHT_0"] = LoadTexture("resources/images/sprites/toad/FireToad_Firing.png");
	textures["FireToadThrowingFireball_LEFT_0"] = flipTexture(textures["FireToadThrowingFireball_RIGHT_0"]);

	textures["TransitioningToad_RIGHT_0"] = textures["SuperToad_RIGHT_0"];
	textures["TransitioningToad_LEFT_0"] = textures["SuperToad_LEFT_0"];
	textures["TransitioningFireToad_RIGHT_0"] = textures["FireToad_RIGHT_0"];
	textures["TransitioningFireToad_LEFT_0"] = textures["FireToad_LEFT_0"];

	//tile
	for (int i = 0; i <= 115; i++) {
		std::string path = "resources/images/tiles/AllTiles/tile_" + std::to_string(i) + ".png";
		textures["TILE_" + std::to_string(i)] = LoadTexture(path.c_str());
	}
		// brick
	textures["Brick_1"] = LoadTexture("resources/images/tiles/AllTiles/tile_110.png");
		// question block
	textures["QUESTION_0"] = LoadTexture("resources/images/sprites/blocks/Question_0.png");
	textures["QUESTION_1"] = LoadTexture("resources/images/sprites/blocks/Question_1.png");
	textures["QUESTION_2"] = LoadTexture("resources/images/sprites/blocks/Question_2.png");
	textures["QUESTION_3"] = LoadTexture("resources/images/sprites/blocks/Question_3.png");
	textures["EyesClosed_0"] = LoadTexture("resources/images/sprites/blocks/EyesClosed_0.png");
		// note block
	textures["NOTE_0"] = LoadTexture("resources/images/sprites/blocks/Note_0.png");
	textures["NOTE_1"] = LoadTexture("resources/images/sprites/blocks/Note_1.png");
	textures["NOTE_2"] = LoadTexture("resources/images/sprites/blocks/Note_2.png");
	textures["NOTE_3"] = LoadTexture("resources/images/sprites/blocks/Note_3.png");
		// rotating block
	textures["ROTATING_0"] = LoadTexture("resources/images/sprites/blocks/Rotating_0.png");
	textures["ROTATING_1"] = LoadTexture("resources/images/sprites/blocks/Rotating_1.png");
	textures["ROTATING_2"] = LoadTexture("resources/images/sprites/blocks/Rotating_2.png");
	textures["ROTATING_3"] = LoadTexture("resources/images/sprites/blocks/Rotating_3.png");
	
	// background

	textures["BACKGROUND_1"] = LoadTexture("resources/images/backgrounds/background1.png");
	textures["BACKGROUND_2"] = LoadTexture("resources/images/backgrounds/background2.png");
	textures["BACKGROUND_3"] = LoadTexture("resources/images/backgrounds/background3.png");
	textures["MENU_SCREEN"] = LoadTexture("resources/images/backgrounds/titlemario.png");
	textures["BACKGROUND_8"] = LoadTexture("resources/images/backgrounds/background8.png");
	textures["WHITE"] = LoadTexture("resources/images/backgrounds/white.png");
	textures["SelectionBackground"] = LoadTexture("resources/images/backgrounds/SelectCharacter.png");
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
	textures["LuigiGUI"] = LoadTexture("resources/images/gui/Luigi_.png");
	textures["MarioGUI"] = LoadTexture("resources/images/gui/Mario_.png");
	textures["Mario_start"] = LoadTexture("resources/images/gui/Mario_start.png");
	textures["Luigi_start"] = LoadTexture("resources/images/gui/Luigi_start.png");
	textures["GameOver"] = LoadTexture("resources/images/gui/guiGameOver.png");
	textures["Time_Up"] = LoadTexture("resources/images/gui/guiTimeUp.png");
	textures["P1GUI"] = LoadTexture("resources/images/gui/P1GUI.png");
	textures["P2GUI"] = LoadTexture("resources/images/gui/P2GUI.png");	

	// coin
	textures["Coin_0"] = LoadTexture("resources/images/sprites/items/Coin_0.png");
	textures["Coin_1"] = LoadTexture("resources/images/sprites/items/Coin_1.png");
	textures["Coin_2"] = LoadTexture("resources/images/sprites/items/Coin_2.png");
	textures["Coin_3"] = LoadTexture("resources/images/sprites/items/Coin_3.png");

	// fireflower
	textures["FireFlower_0"] = LoadTexture("resources/images/sprites/items/FireFlower_0.png");
	textures["FireFlower_1"] = LoadTexture("resources/images/sprites/items/FireFlower_1.png");
	// mushroom 
	textures["GreenMushroom"] = LoadTexture("resources/images/sprites/items/1UpMushroom.png");
	textures["RedMushroom"] = LoadTexture("resources/images/sprites/items/Mushroom.png");
	// star
	textures["YellowStar"] = LoadTexture("resources/images/sprites/items/Star.png");
	textures["BlueStar"] = LoadTexture("resources/images/sprites/items/blue_star.png");

	textures["Moon"] = LoadTexture("resources/images/sprites/items/3UpMoon.png");
	
	// smoke effect
	textures["Puft_0"] = LoadTexture("resources/images/sprites/effects/Puft_0.png");
	textures["Puft_1"] = LoadTexture("resources/images/sprites/effects/Puft_1.png");
	textures["Puft_2"] = LoadTexture("resources/images/sprites/effects/Puft_2.png");
	textures["Puft_3"] = LoadTexture("resources/images/sprites/effects/Puft_3.png");
	// dust effect
	textures["Dust_0"] = LoadTexture("resources/images/sprites/effects/StarDust_0.png");
	textures["Dust_1"] = LoadTexture("resources/images/sprites/effects/StarDust_1.png");
	textures["Dust_2"] = LoadTexture("resources/images/sprites/effects/StarDust_2.png");
	textures["Dust_3"] = LoadTexture("resources/images/sprites/effects/StarDust_3.png");
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
	// yellow koopa
	textures["YellowKoopa_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/YellowKoopaTroopa_0.png");
	textures["YellowKoopa_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/YellowKoopaTroopa_1.png");
	textures["YellowKoopa_LEFT_0"] = flipTexture(textures["YellowKoopa_RIGHT_0"]);
	textures["YellowKoopa_LEFT_1"] = flipTexture(textures["YellowKoopa_RIGHT_1"]);
	textures["YellowKoopa_Shell"] = LoadTexture("resources/images/sprites/baddies/yellow_shell_3.png");
	textures["YellowKoopa_Shell_0"] = LoadTexture("resources/images/sprites/baddies/yellow_shell_0.png");
	textures["YellowKoopa_Shell_1"] = LoadTexture("resources/images/sprites/baddies/yellow_shell_1.png");
	textures["YellowKoopa_Shell_2"] = LoadTexture("resources/images/sprites/baddies/yellow_shell_2.png");
	textures["YellowKoopa_Shell_3"] = LoadTexture("resources/images/sprites/baddies/yellow_shell_3.png");
	// green koopa
	textures["GreenKoopa_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/GreenKoopaTroopa_0.png");
	textures["GreenKoopa_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/GreenKoopaTroopa_1.png");
	textures["GreenKoopa_LEFT_0"] = flipTexture(textures["GreenKoopa_RIGHT_0"]);
	textures["GreenKoopa_LEFT_1"] = flipTexture(textures["GreenKoopa_RIGHT_1"]);
	textures["GreenKoopa_Shell"] = LoadTexture("resources/images/sprites/baddies/green_shell_3.png");
	textures["GreenKoopa_Shell_0"] = LoadTexture("resources/images/sprites/baddies/green_shell_0.png");
	textures["GreenKoopa_Shell_1"] = LoadTexture("resources/images/sprites/baddies/green_shell_1.png");
	textures["GreenKoopa_Shell_2"] = LoadTexture("resources/images/sprites/baddies/green_shell_2.png");
	textures["GreenKoopa_Shell_3"] = LoadTexture("resources/images/sprites/baddies/green_shell_3.png");
	// red koopa
	textures["RedKoopa_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/RedKoopaTroopa_0.png");
	textures["RedKoopa_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/RedKoopaTroopa_1.png");
	textures["RedKoopa_LEFT_0"] = flipTexture(textures["RedKoopa_RIGHT_0"]);
	textures["RedKoopa_LEFT_1"] = flipTexture(textures["RedKoopa_RIGHT_1"]);
	textures["RedKoopa_Shell"] = LoadTexture("resources/images/sprites/baddies/red_shell_3.png");
	textures["RedKoopa_Shell_0"] = LoadTexture("resources/images/sprites/baddies/red_shell_0.png");
	textures["RedKoopa_Shell_1"] = LoadTexture("resources/images/sprites/baddies/red_shell_1.png");
	textures["RedKoopa_Shell_2"] = LoadTexture("resources/images/sprites/baddies/red_shell_2.png");
	textures["RedKoopa_Shell_3"] = LoadTexture("resources/images/sprites/baddies/red_shell_3.png");
	// blue koopa
	textures["BlueKoopa_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/BlueKoopaTroopa_0.png");
	textures["BlueKoopa_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/BlueKoopaTroopa_1.png");
	textures["BlueKoopa_LEFT_0"] = flipTexture(textures["BlueKoopa_RIGHT_0"]);
	textures["BlueKoopa_LEFT_1"] = flipTexture(textures["BlueKoopa_RIGHT_1"]);
	textures["BlueKoopa_Shell"] = LoadTexture("resources/images/sprites/baddies/blue_shell_3.png");
	textures["BlueKoopa_Shell_0"] = LoadTexture("resources/images/sprites/baddies/blue_shell_0.png");
	textures["BlueKoopa_Shell_1"] = LoadTexture("resources/images/sprites/baddies/blue_shell_1.png");
	textures["BlueKoopa_Shell_2"] = LoadTexture("resources/images/sprites/baddies/blue_shell_2.png");
	textures["BlueKoopa_Shell_3"] = LoadTexture("resources/images/sprites/baddies/blue_shell_3.png");

	// parakoopa
	textures["ParaKoopaRed_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/ParaKoopaRed_0.png");
	textures["ParaKoopaRed_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/ParaKoopaRed_1.png");
	textures["ParaKoopaRed_LEFT_0"] = flipTexture(textures["ParaKoopaRed_RIGHT_0"]);
	textures["ParaKoopaRed_LEFT_1"] = flipTexture(textures["ParaKoopaRed_RIGHT_1"]);

	textures["ParaKoopaBlue_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/ParaKoopaBlue_0.png");
	textures["ParaKoopaBlue_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/ParaKoopaBlue_1.png");
	textures["ParaKoopaBlue_LEFT_0"] = flipTexture(textures["ParaKoopaBlue_RIGHT_0"]);
	textures["ParaKoopaBlue_LEFT_1"] = flipTexture(textures["ParaKoopaBlue_RIGHT_1"]);

	// bullet
	textures["Bullet_RIGHT"] = LoadTexture("resources/images/sprites/baddies/BulletBill_0.png");
	textures["BenzaiBill_RIGHT"] = LoadTexture("resources/images/sprites/baddies/BanzaiBill_0.png");
	textures["Bullet_LEFT"] = flipTexture(textures["Bullet_RIGHT"]);
	textures["BenzaiBill_LEFT"] = flipTexture(textures["BenzaiBill_RIGHT"]);
	textures["Bullet_Dead"] = textures["Bullet_RIGHT"];
	textures["BenzaiBill_Dead"] = textures["BenzaiBill_RIGHT"];
	// enemy fireball
	textures["EnemyFireball_RIGHT_0"] = ConvertFireballToBlue(textures["FlowerMarioFireball_RIGHT_0"]);
	textures["EnemyFireball_RIGHT_1"] = ConvertFireballToBlue(textures["FlowerMarioFireball_RIGHT_1"]);
	textures["EnemyFireball_RIGHT_2"] = ConvertFireballToBlue(textures["FlowerMarioFireball_RIGHT_2"]);
	textures["EnemyFireball_RIGHT_3"] = ConvertFireballToBlue(textures["FlowerMarioFireball_RIGHT_3"]);
	textures["EnemyFireball_LEFT_0"] = flipTexture(textures["EnemyFireball_RIGHT_0"]);
	textures["EnemyFireball_LEFT_1"] = flipTexture(textures["EnemyFireball_RIGHT_1"]);
	textures["EnemyFireball_LEFT_2"] = flipTexture(textures["EnemyFireball_RIGHT_2"]);
	textures["EnemyFireball_LEFT_3"] = flipTexture(textures["EnemyFireball_RIGHT_3"]);

	textures["PiranhaPlant_OPEN"] = LoadTexture("resources/images/sprites/baddies/PiranhaPlant_0.png");
	textures["PiranhaPlant_CLOSED"] = LoadTexture("resources/images/sprites/baddies/PiranhaPlant_1.png");
	textures["FirePiranhaPlant_OPEN"] = textures["PiranhaPlant_OPEN"];
	textures["FirePiranhaPlant_CLOSED"] = textures["PiranhaPlant_CLOSED"];
	textures["PiranhaPlant_JUMP_UP_0"] = LoadTexture("resources/images/sprites/baddies/PiranhaPlant_JUMP_UP_0.png");
	textures["PiranhaPlant_JUMP_DOWN_0"] = LoadTexture("resources/images/sprites/baddies/PiranhaPlant_JUMP_DOWN_0.png");
	textures["PiranhaPlant_JUMP_UP_1"] = LoadTexture("resources/images/sprites/baddies/PiranhaPlant_JUMP_UP_1.png");
	textures["PiranhaPlant_JUMP_DOWN_1"] = LoadTexture("resources/images/sprites/baddies/PiranhaPlant_JUMP_DOWN_1.png");
	// rex
	textures["Rex_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/Rex_2_0.png");
	textures["Rex_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/Rex_2_1.png");
	textures["Rex_LEFT_0"] = flipTexture(textures["Rex_RIGHT_0"]);
	textures["Rex_LEFT_1"] = flipTexture(textures["Rex_RIGHT_1"]);
	textures["Rex_Compressed_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/Rex_1_0.png");
	textures["Rex_Compressed_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/Rex_1_1.png");
	textures["Rex_Compressed_LEFT_0"] = flipTexture(textures["Rex_Compressed_RIGHT_0"]);
	textures["Rex_Compressed_LEFT_1"] = flipTexture(textures["Rex_Compressed_RIGHT_1"]);
	textures["Rex_Dead"] = textures["Rex_Dead.png"];
	// muncher
	textures["Muncher_0"] = LoadTexture("resources/images/sprites/baddies/Muncher_0.png");
	textures["Muncher_1"] = LoadTexture("resources/images/sprites/baddies/Muncher_1.png");
	// bobomb
	textures["Bobomb_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/BobOmb_0.png");
	textures["Bobomb_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/BobOmb_1.png");
	textures["Bobomb_LEFT_0"] = flipTexture(textures["Bobomb_RIGHT_0"]);
	textures["Bobomb_LEFT_1"] = flipTexture(textures["Bobomb_RIGHT_1"]);
	textures["BobOmb_Activated_0"] = textures["Bobomb_RIGHT_0"];
	textures["BobOmb_Activated_1"] = textures["Bobomb_RIGHT_1"];
	textures["BobOmb_Explosion"] = LoadTexture("resources/images/sprites/baddies/BobOmb_0.png");
	//textures["DryBones_Collapse"] = LoadTexture("resources/images/sprites/baddies/DryBones_Collapse.png");
	
	// spiny
	textures["Spiny_LEFT_0"] = LoadTexture("resources/images/sprites/baddies/Spiny_LEFT_0.png");
	textures["Spiny_LEFT_1"] = LoadTexture("resources/images/sprites/baddies/Spiny_LEFT_1.png");
	textures["Spiny_RIGHT_0"] = flipTexture(textures["Spiny_LEFT_0"]);
	textures["Spiny_RIGHT_1"] = flipTexture(textures["Spiny_LEFT_1"]);
	textures["Spiny_DEAD"] = LoadTexture("resources/images/sprites/baddies/Spiny_DEAD.png");
	// buzzybeetle
	textures["BuzzyBeetle_RIGHT_0"] = LoadTexture("resources/images/sprites/baddies/BuzzyBeetle_0.png");
	textures["BuzzyBeetle_RIGHT_1"] = LoadTexture("resources/images/sprites/baddies/BuzzyBeetle_1.png");
	textures["BuzzyBeetle_LEFT_0"] = flipTexture(textures["BuzzyBeetle_RIGHT_0"]);
	textures["BuzzyBeetle_lEFT_1"] = flipTexture(textures["BuzzyBeetle_RIGHT_1"]);
	textures["BuzzyBeetle_Shell_2"] = LoadTexture("resources/images/sprites/baddies/BuzzyBeetle_Shell_2.png");
	textures["BuzzyBeetle_Shell_1"] = LoadTexture("resources/images/sprites/baddies/BuzzyBeetle_Shell_1.png");
	textures["BuzzyBeetle_Shell_0"] = LoadTexture("resources/images/sprites/baddies/BuzzyBeetle_Shell_0.png");

	//BoomBoom
	textures["boomboom_walk_right_0"] = LoadTexture("resources/images/sprites/baddies/boomboom_walk_0.png");
	textures["boomboom_walk_right_1"] = LoadTexture("resources/images/sprites/baddies/boomboom_walk_1.png");
	textures["boomboom_walk_right_2"] = LoadTexture("resources/images/sprites/baddies/boomboom_walk_2.png");
	textures["boomboom_walk_left_0"] = flipTexture(textures["boomboom_walk_right_0"]);
	textures["boomboom_walk_left_1"] = flipTexture(textures["boomboom_walk_right_1"]);
	textures["boomboom_walk_left_2"] = flipTexture(textures["boomboom_walk_right_2"]);
	textures["boomboom_spin"] = LoadTexture("resources/images/sprites/baddies/boomboom_spin.png");
	textures["boomboom_jump"] = LoadTexture("resources/images/sprites/baddies/boomboom_jump.png");
	textures["boomboom_charge"] = LoadTexture("resources/images/sprites/baddies/boomboom_charge.png");
	textures["boomboom_stunned"] = LoadTexture("resources/images/sprites/baddies/boomboom_stunned.png");
	textures["boomboom_hidden"] = LoadTexture("resources/images/sprites/baddies/boomboom_hidden.png");
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
	std::string soundfolder = std::string(GetWorkingDirectory()) + "/resources/sounds/";
	try {
		for (const auto& entry : fs::directory_iterator(soundfolder)) {
			if (entry.is_regular_file() && entry.path().extension() == ".wav") {
				std::string filename = entry.path().filename().string(); // e.g., "jump.wav"
				std::string fullPath = entry.path().string();             // full path for raylib

				sounds[filename] = LoadSound(fullPath.c_str());
			}
		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "[Filesystem error]" << e.what() << std::endl;
		std::cerr << "-> Path: " << soundfolder << std::endl;
	}
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

Texture2D ResourceManager::ConvertFireballToBlue(Texture2D fireballTexture) {
	Image image = LoadImageFromTexture(fireballTexture);
	Color* pixels = LoadImageColors(image);
	int count = image.width * image.height;

	for (int i = 0; i < count; i++) {
		if (IsColorNear(pixels[i], CLITERAL(Color){184, 40, 0, 255})) {
			pixels[i] = CLITERAL(Color) { 0, 48, 160, 255 }; // dark blue
		}
		else if (IsColorNear(pixels[i], CLITERAL(Color){248, 120, 0, 255})) {
			pixels[i] = CLITERAL(Color) { 32, 96, 224, 255 }; // mid blue
		}
		else if (IsColorNear(pixels[i], CLITERAL(Color){248, 136, 0, 255})) {
			pixels[i] = CLITERAL(Color) { 80, 144, 255, 255 }; // light blue
		}
		else if (IsColorNear(pixels[i], CLITERAL(Color){248, 192, 0, 255})) {
			pixels[i] = CLITERAL(Color) { 160, 200, 255, 255 }; // very light blue
		}
	}

	MemFree(image.data); // Free original data
	image.data = pixels;

	Texture2D blueFireball = LoadTextureFromImage(image);
	UnloadImage(image);
	return blueFireball;
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

