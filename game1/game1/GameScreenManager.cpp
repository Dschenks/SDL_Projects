#include "GameScreenManager.h"
#include <stdio.h>

GameScreenManager::GameScreenManager() :
	game(0), gameScreens(0), numGameScreens(0)
{
}

void GameScreenManager::setGame(Game* game)
{
	this->game = game;
}

GameScreenManager::gameScreenID GameScreenManager::addGameScreen(GameScreen* gameScreen)
{
	GameScreen** t = new GameScreen*[numGameScreens + 1];
	for (int i = 0; i < numGameScreens; i++) t[i] = gameScreens[i];
	delete[] gameScreens;
	gameScreens = t;
	gameScreens[numGameScreens] = gameScreen;
	numGameScreens++;
	
	return numGameScreens - 1;
}

int GameScreenManager::changeGameScreen(size_t index)
{
	if (index >= numGameScreens) {
		printf("Cannot change screen to invalid index %llu\n", index);
		return -1;
	}
	game->setCurrentScreen(gameScreens[index]);
	return 0;
}
