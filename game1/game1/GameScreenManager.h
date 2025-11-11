#pragma once
#include "GameScreen.h"
#include "Game.h"

class GameScreenManager
{
public:
	GameScreenManager();

	void setGame(Game* game);

	void addGameScreen(GameScreen* gameScreen);
	void changeGameScreen(size_t index);

private:
	Game* game;
	GameScreen** gameScreens;
	size_t numGameScreens;
};

