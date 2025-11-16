#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Game.h"
#include "Player.h"
#include "GameScreenManager.h"
#include "gameTime.h"

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
		// GameScreen1
		GameScreen screen1;
		Player player;

		player.setSpriteTexure(knight + "Knight-Idle.png", spriteFlags::SPRITE_STANDING);
		player.setSpriteTexure(knight + "Knight-Walk.png", spriteFlags::SPRITE_RUNNING_LEFT);
		player.setSpriteTexure(knight + "Knight-Walk.png", spriteFlags::SPRITE_RUNNING_RIGHT);
		player.setSpriteTexure(knight + "Knight-Walk.png", spriteFlags::SPRITE_RUNNING_UP);
		player.setSpriteTexure(knight + "Knight-Walk.png", spriteFlags::SPRITE_RUNNING_DOWN);
		
		fps idleFps = 10;
		fps runningFps = 15;

		player.setSpriteFps(spriteFlags::SPRITE_STANDING, idleFps);
		player.setSpriteFps(spriteFlags::SPRITE_RUNNING_LEFT, runningFps);
		player.setSpriteFps(spriteFlags::SPRITE_RUNNING_RIGHT, runningFps);
		player.setSpriteFps(spriteFlags::SPRITE_RUNNING_UP, runningFps);
		player.setSpriteFps(spriteFlags::SPRITE_RUNNING_DOWN, runningFps);

		spriteModifier_t spriteMod = { 0 };
		spriteMod.srcRectSet = true;
		spriteMod.srcRect.w = 100;
		spriteMod.srcRect.h = 100;
		spriteMod.srcRect.y = 0;
		for (int i = 0; i < 6; i++) {
			spriteMod.srcRect.x = 100 * i;
			player.addSpriteFrame(spriteFlags::SPRITE_STANDING, spriteMod);
		}
		spriteMod.flipSet = true;
		spriteMod.flip = SDL_FLIP_HORIZONTAL;
		for (int i = 0; i < 6; i++) {
			spriteMod.srcRect.x = 100 * i;
			player.addSpriteFrame(spriteFlags::SPRITE_RUNNING_LEFT, spriteMod);
		}
		spriteMod.flipSet = false;
		for (int i = 0; i < 6; i++) {
			spriteMod.srcRect.x = 100 * i;
			player.addSpriteFrame(spriteFlags::SPRITE_RUNNING_RIGHT, spriteMod);
		}
		for (int i = 0; i < 6; i++) {
			spriteMod.srcRect.x = 100 * i;
			player.addSpriteFrame(spriteFlags::SPRITE_RUNNING_UP, spriteMod);
		}
		for (int i = 0; i < 6; i++) {
			spriteMod.srcRect.x = 100 * i;
			player.addSpriteFrame(spriteFlags::SPRITE_RUNNING_DOWN, spriteMod);
		}
		player.setSpeed(5);
		player.setScale(5);

		screen1.addGameObject(player.getGameObject());
		
		gameScreenID screen1_ID = screenManager.addGameScreen(&screen1);
		if (screenManager.changeGameScreen(screen1_ID) < 0) return -1;
		/*game.setCurrentScreen(&screen1);*/
		while (game.tick()) {};
	}
	
	return 0;
}