#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Game.h"
#include "Player.h"
#include "GameScreenManager.h"
#include "gameTime.h"
#include "GameMap.h"

using gameScreenID = GameScreenManager::gameScreenID;
using spriteFlags = SpriteTypes::spriteAssetFlags_t;

Game game;
GameScreenManager screenManager;
const std::string assetsDir = "C:\\Users\\dento\\source\\repos\\SDL_projects\\assets\\";

int main(int agrc, char* args[]) {
	game = Game();

	bool init_f = true;
	if (game.init() < 0) {
		printf("Failed to initialize!\n");
		init_f = false;
	}
	//if (!( init_f &= loadMedia() )) printf("Failed to Load Media!\n");
	game.setBaseAssetPath(assetsDir);
	game.getGameClock()->setFrameRate((GameTime::fps)30);
	screenManager.setGame(&game);

	if (init_f) {
		std::string rpgAsset = "rpg_assets\\Tiny RPG Character Asset Pack v1.03 -Full 20 Characters\\";
		std::string characters = rpgAsset + "Characters(100x100)\\";
		std::string knight = characters + "Knight\\Knight\\";
		std::string knightIdle = knight + "Knight-Idle.png";
		std::string knightRun = knight + "Knight-Walk.png";
		// GameScreen1
		GameScreen screen1;
		Player player;

		player.setSpriteTexure(knightIdle, spriteFlags::SPRITE_STANDING);
		player.setSpriteTexure(knightRun, spriteFlags::SPRITE_RUNNING_RIGHT);

		fps idleFps = 10;
		fps runningFps = 15;

		player.setSpriteFps(spriteFlags::SPRITE_STANDING, idleFps);
		player.setSpriteFps(spriteFlags::SPRITE_RUNNING_RIGHT, runningFps);

		spriteModifier_t spriteMod = { 0 };
		spriteMod.srcRectSet = true;
		spriteMod.srcRect.w = 100;
		spriteMod.srcRect.h = 100;
		spriteMod.srcRect.y = 0;
		for (int i = 0; i < 6; i++) {
			spriteMod.srcRect.x = 100 * i;
			player.addSpriteFrame(spriteFlags::SPRITE_STANDING, spriteMod);
		}
		for (int i = 0; i < 6; i++) {
			spriteMod.srcRect.x = 100 * i;
			player.addSpriteFrame(spriteFlags::SPRITE_RUNNING_RIGHT, spriteMod);
		}
		player.setSpeed(5);
		player.setScale(5);


		std::string mapTilesPath = "rpg_assets\\rpg_assets\\2D Dungeon Asset Pack_v5.2\\character and tileset\\Dungeon_Tileset_v2.png";
		GameMap map;
		int tileScale = 5;
		SDL_Rect tileDest = {0, 0, 16 * tileScale, 16 * tileScale };
		map.setTileSize(tileDest.w, tileDest.h);
		double tileSize = 16.0 * tileScale;
		map.setMapWidth(((int)ceil(WindowScreen::getScreenWidth() / tileSize)));
		map.setMapHeight(((int)ceil(WindowScreen::getScreenHeight() / tileSize)));
		SDL_Rect r = {16 * 6, 0, 16, 16};
		GameMap::tileID id = map.addTileSprite(mapTilesPath, r);
		for (int i = 0; i < map.getMapWidth(); i++) {
			for (int j = 0; j < map.getMapHeight(); j++) {
				map.setTile(i, j, id);
			}
		}

		screen1.addGameObject(&map.gameObject);
		screen1.addGameObject(player.getGameObject());
		 
		gameScreenID screen1_ID = screenManager.addGameScreen(&screen1);
		if (screenManager.changeGameScreen(screen1_ID) < 0) return -1;
		/*game.setCurrentScreen(&screen1);*/
		while (game.tick()) {};
	}
	
	return 0;
}