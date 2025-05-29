#include "../include/ResourceManager.h"

std::map<std::string, Texture2D> ResourceManager::textures;

void ResourceManager::loadTextures() {
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
	// tile
	textures["TILE_1"] = LoadTexture("resources/images/tiles/AllTiles/tile_1.png");
	textures["TILE_2"] = LoadTexture("resources/images/tiles/AllTiles/tile_2.png");
	textures["TILE_3"] = LoadTexture("resources/images/tiles/AllTiles/tile_3.png");
	textures["TILE_4"] = LoadTexture("resources/images/tiles/AllTiles/tile_4.png");
	textures["TILE_5"] = LoadTexture("resources/images/tiles/AllTiles/tile_5.png");
	textures["TILE_6"] = LoadTexture("resources/images/tiles/AllTiles/tile_6.png");
	textures["TILE_7"] = LoadTexture("resources/images/tiles/AllTiles/tile_7.png");
	textures["TILE_8"] = LoadTexture("resources/images/tiles/AllTiles/tile_8.png");
	textures["TILE_9"] = LoadTexture("resources/images/tiles/AllTiles/tile_9.png");
	textures["TILE_10"] = LoadTexture("resources/images/tiles/AllTiles/tile_10.png");
	textures["TILE_11"] = LoadTexture("resources/images/tiles/AllTiles/tile_11.png");
	textures["TILE_12"] = LoadTexture("resources/images/tiles/AllTiles/tile_12.png");
	textures["TILE_13"] = LoadTexture("resources/images/tiles/AllTiles/tile_13.png");
	textures["TILE_14"] = LoadTexture("resources/images/tiles/AllTiles/tile_14.png");
	textures["TILE_15"] = LoadTexture("resources/images/tiles/AllTiles/tile_15.png");
	textures["TILE_16"] = LoadTexture("resources/images/tiles/AllTiles/tile_16.png");
	textures["TILE_17"] = LoadTexture("resources/images/tiles/AllTiles/tile_17.png");
	textures["TILE_18"] = LoadTexture("resources/images/tiles/AllTiles/tile_18.png");
	textures["TILE_19"] = LoadTexture("resources/images/tiles/AllTiles/tile_19.png");
	textures["TILE_20"] = LoadTexture("resources/images/tiles/AllTiles/tile_20.png");
	textures["TILE_21"] = LoadTexture("resources/images/tiles/AllTiles/tile_21.png");
	textures["TILE_22"] = LoadTexture("resources/images/tiles/AllTiles/tile_22.png");
	textures["TILE_23"] = LoadTexture("resources/images/tiles/AllTiles/tile_23.png");
	textures["TILE_24"] = LoadTexture("resources/images/tiles/AllTiles/tile_24.png");
	textures["TILE_25"] = LoadTexture("resources/images/tiles/AllTiles/tile_25.png");
	textures["TILE_26"] = LoadTexture("resources/images/tiles/AllTiles/tile_26.png");
	textures["TILE_27"] = LoadTexture("resources/images/tiles/AllTiles/tile_27.png");
	textures["TILE_28"] = LoadTexture("resources/images/tiles/AllTiles/tile_28.png");
	textures["TILE_29"] = LoadTexture("resources/images/tiles/AllTiles/tile_29.png");
	textures["TILE_30"] = LoadTexture("resources/images/tiles/AllTiles/tile_30.png");
	textures["TILE_31"] = LoadTexture("resources/images/tiles/AllTiles/tile_31.png");
	textures["TILE_32"] = LoadTexture("resources/images/tiles/AllTiles/tile_32.png");
	textures["TILE_33"] = LoadTexture("resources/images/tiles/AllTiles/tile_33.png");
	textures["TILE_34"] = LoadTexture("resources/images/tiles/AllTiles/tile_34.png");
	textures["TILE_35"] = LoadTexture("resources/images/tiles/AllTiles/tile_35.png");
	textures["TILE_36"] = LoadTexture("resources/images/tiles/AllTiles/tile_36.png");
	textures["TILE_37"] = LoadTexture("resources/images/tiles/AllTiles/tile_37.png");
	textures["TILE_38"] = LoadTexture("resources/images/tiles/AllTiles/tile_38.png");
	textures["TILE_39"] = LoadTexture("resources/images/tiles/AllTiles/tile_39.png");
	textures["TILE_40"] = LoadTexture("resources/images/tiles/AllTiles/tile_40.png");
	textures["TILE_41"] = LoadTexture("resources/images/tiles/AllTiles/tile_41.png");
	textures["TILE_42"] = LoadTexture("resources/images/tiles/AllTiles/tile_42.png");
	textures["TILE_43"] = LoadTexture("resources/images/tiles/AllTiles/tile_43.png");
	textures["TILE_44"] = LoadTexture("resources/images/tiles/AllTiles/tile_44.png");
	textures["TILE_45"] = LoadTexture("resources/images/tiles/AllTiles/tile_45.png");
	textures["TILE_46"] = LoadTexture("resources/images/tiles/AllTiles/tile_46.png");
	textures["TILE_47"] = LoadTexture("resources/images/tiles/AllTiles/tile_47.png");
	textures["TILE_48"] = LoadTexture("resources/images/tiles/AllTiles/tile_48.png");
	textures["TILE_49"] = LoadTexture("resources/images/tiles/AllTiles/tile_49.png");
	textures["TILE_50"] = LoadTexture("resources/images/tiles/AllTiles/tile_50.png");
	textures["TILE_51"] = LoadTexture("resources/images/tiles/AllTiles/tile_51.png");
	textures["TILE_52"] = LoadTexture("resources/images/tiles/AllTiles/tile_52.png");
	textures["TILE_53"] = LoadTexture("resources/images/tiles/AllTiles/tile_53.png");
	textures["TILE_54"] = LoadTexture("resources/images/tiles/AllTiles/tile_54.png");
	textures["TILE_55"] = LoadTexture("resources/images/tiles/AllTiles/tile_55.png");
	textures["TILE_56"] = LoadTexture("resources/images/tiles/AllTiles/tile_56.png");
	textures["TILE_57"] = LoadTexture("resources/images/tiles/AllTiles/tile_57.png");
	textures["TILE_58"] = LoadTexture("resources/images/tiles/AllTiles/tile_58.png");
	textures["TILE_59"] = LoadTexture("resources/images/tiles/AllTiles/tile_59.png");
	textures["TILE_60"] = LoadTexture("resources/images/tiles/AllTiles/tile_60.png");
	textures["TILE_61"] = LoadTexture("resources/images/tiles/AllTiles/tile_61.png");
	textures["TILE_62"] = LoadTexture("resources/images/tiles/AllTiles/tile_62.png");
	textures["TILE_63"] = LoadTexture("resources/images/tiles/AllTiles/tile_63.png");
	textures["TILE_64"] = LoadTexture("resources/images/tiles/AllTiles/tile_64.png");
	textures["TILE_65"] = LoadTexture("resources/images/tiles/AllTiles/tile_65.png");
	textures["TILE_66"] = LoadTexture("resources/images/tiles/AllTiles/tile_66.png");
	textures["TILE_67"] = LoadTexture("resources/images/tiles/AllTiles/tile_67.png");
	textures["TILE_68"] = LoadTexture("resources/images/tiles/AllTiles/tile_68.png");
	textures["TILE_69"] = LoadTexture("resources/images/tiles/AllTiles/tile_69.png");
	textures["TILE_70"] = LoadTexture("resources/images/tiles/AllTiles/tile_70.png");
	textures["TILE_71"] = LoadTexture("resources/images/tiles/AllTiles/tile_71.png");
	textures["TILE_72"] = LoadTexture("resources/images/tiles/AllTiles/tile_72.png");
	textures["TILE_73"] = LoadTexture("resources/images/tiles/AllTiles/tile_73.png");
	textures["TILE_74"] = LoadTexture("resources/images/tiles/AllTiles/tile_74.png");
	textures["TILE_75"] = LoadTexture("resources/images/tiles/AllTiles/tile_75.png");
	textures["TILE_76"] = LoadTexture("resources/images/tiles/AllTiles/tile_76.png");
	textures["TILE_77"] = LoadTexture("resources/images/tiles/AllTiles/tile_77.png");
	textures["TILE_78"] = LoadTexture("resources/images/tiles/AllTiles/tile_78.png");
	textures["TILE_79"] = LoadTexture("resources/images/tiles/AllTiles/tile_79.png");
	textures["TILE_80"] = LoadTexture("resources/images/tiles/AllTiles/tile_80.png");
	textures["TILE_81"] = LoadTexture("resources/images/tiles/AllTiles/tile_81.png");
	textures["TILE_82"] = LoadTexture("resources/images/tiles/AllTiles/tile_82.png");
	textures["TILE_83"] = LoadTexture("resources/images/tiles/AllTiles/tile_83.png");
	textures["TILE_84"] = LoadTexture("resources/images/tiles/AllTiles/tile_84.png");
	textures["TILE_85"] = LoadTexture("resources/images/tiles/AllTiles/tile_85.png");
	textures["TILE_86"] = LoadTexture("resources/images/tiles/AllTiles/tile_86.png");
	textures["TILE_87"] = LoadTexture("resources/images/tiles/AllTiles/tile_87.png");
	textures["TILE_88"] = LoadTexture("resources/images/tiles/AllTiles/tile_88.png");
	textures["TILE_89"] = LoadTexture("resources/images/tiles/AllTiles/tile_89.png");
	textures["TILE_90"] = LoadTexture("resources/images/tiles/AllTiles/tile_90.png");
	textures["TILE_91"] = LoadTexture("resources/images/tiles/AllTiles/tile_91.png");
	textures["TILE_92"] = LoadTexture("resources/images/tiles/AllTiles/tile_92.png");
	textures["TILE_93"] = LoadTexture("resources/images/tiles/AllTiles/tile_93.png");
	textures["TILE_94"] = LoadTexture("resources/images/tiles/AllTiles/tile_94.png");
	textures["TILE_95"] = LoadTexture("resources/images/tiles/AllTiles/tile_95.png");
	textures["TILE_96"] = LoadTexture("resources/images/tiles/AllTiles/tile_96.png");
	textures["TILE_97"] = LoadTexture("resources/images/tiles/AllTiles/tile_97.png");
	textures["TILE_98"] = LoadTexture("resources/images/tiles/AllTiles/tile_98.png");
	textures["TILE_99"] = LoadTexture("resources/images/tiles/AllTiles/tile_99.png");
	textures["TILE_100"] = LoadTexture("resources/images/tiles/AllTiles/tile_100.png");
	textures["TILE_101"] = LoadTexture("resources/images/tiles/AllTiles/tile_101.png");
	textures["TILE_102"] = LoadTexture("resources/images/tiles/AllTiles/tile_102.png");
	textures["TILE_103"] = LoadTexture("resources/images/tiles/AllTiles/tile_103.png");
	textures["TILE_104"] = LoadTexture("resources/images/tiles/AllTiles/tile_104.png");

}

void ResourceManager::unloadTextures() {
	for (auto const &[key, val] : textures) {
		unloadTexture(key);
	}
	textures.clear();
}
void ResourceManager::unloadTexture(std::string key) {
	if (textures.find(key) != textures.end()) {
		UnloadTexture(textures[key]);
	}
}

void ResourceManager::LoadAllResources()
{
	loadTextures();
}

std::map<std::string, Texture2D>  ResourceManager::getTextures() {
	return textures;
}

Texture2D& ResourceManager::getTexture(const std::string name)
{
	return textures[name];
}

void ResourceManager::UnloadAllResources()
{
	unloadTextures();
}

Texture2D flipTexture(Texture2D& a) {
	Image img = LoadImageFromTexture(a);
	ImageFlipHorizontal(&img);
	Texture tex = LoadTextureFromImage(img);
	UnloadImage(img);
	return tex;
}