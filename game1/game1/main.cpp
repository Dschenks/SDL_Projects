#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Game.h"
#include "Player.h"
#include "GameScreenManager.h"

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
	game.setFrameRate((Game::fps)15);
	screenManager.setGame(&game);

	if (init_f) {
		GameScreen screen1;
		Player p;
		p.setSprite("red_face_50_50.png", SpriteTypes::SPRITE_STANDING_1);
		screen1.addGameObject(p.getGameObject());

		GameScreen screen2;
		Player p2;
		p2.setSprite("knight_standing_1_32_32.png", SpriteTypes::SPRITE_STANDING_1);
		p2.setSprite("knight_standing_2_32_32.png", SpriteTypes::SPRITE_STANDING_2);
		p2.setSprite("knight_running_1_32_32.png", SpriteTypes::SPRITE_RUNNING_LEFT_1);
		p2.setSprite("knight_running_2_32_32.png", SpriteTypes::SPRITE_RUNNING_LEFT_2);
		p2.setScaleUp(10);
		screen2.addGameObject(p2.getGameObject());

		screenManager.addGameScreen(&screen1);
		screenManager.addGameScreen(&screen2);
		screenManager.changeGameScreen(1);
		/*game.setCurrentScreen(&screen1);*/
		while (game.tick()) {};
	}
	
	return 0;
}