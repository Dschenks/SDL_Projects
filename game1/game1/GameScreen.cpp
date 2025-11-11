#include "GameScreen.h"
#include "GameTypes.h"
#include "TextureManager.h"

GameScreen::GameScreen() :
	gRenderer(NULL), gameObjList(NULL), gameObjListSize(0)
{
}

GameScreen::~GameScreen()
{
}

void GameScreen::addGameObject(GameObject* newGameObj)
{
	gameObjListSize++;
	GameObject** t = new GameObject*[gameObjListSize];
	for (size_t i = 0; i < gameObjListSize - 1; i++) t[i] = gameObjList[i];
	t[gameObjListSize - 1] = newGameObj;
	delete[] gameObjList;
	gameObjList = t;
}

GameObject* GameScreen::getGameObject(size_t index)
{
	if (index >= gameObjListSize) return NULL;

    return gameObjList[index];
}

void GameScreen::getGameObjectList(GameObject** retList, size_t retListSize) const
{
	retList = gameObjList;
	retListSize = gameObjListSize;
}

void GameScreen::readInput(int input)
{
	for (size_t i = 0; i < gameObjListSize; i++) gameObjList[i]->move((GameTypes::move_dir_t)input);
}

void GameScreen::update()
{
}

void GameScreen::renderScreen()
{
	for (size_t i = 0; i < gameObjListSize; i++) gameObjList[i]->render();
}

void GameScreen::init(WindowScreen* windowScreen, TextureManager* textureManager)
{
	for (size_t i = 0; i < gameObjListSize; i++) gameObjList[i]->init(windowScreen, textureManager);
}

void GameScreen::close()
{
	for (size_t i = 0; i < gameObjListSize; i++) gameObjList[i]->close();
}
