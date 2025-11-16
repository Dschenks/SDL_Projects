#pragma once
#include "GameScreen.h"
#include "Game.h"

class GameScreenManager
{
public:
	typedef size_t gameScreenID;

	GameScreenManager();

	void setGame(Game* game);

	gameScreenID addGameScreen(GameScreen* gameScreen);
	int changeGameScreen(size_t index);

private:
	Game* game;
	GameScreen** gameScreens;
	size_t numGameScreens;
};

