#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "WindowScreen.h"
#include "TextureManager.h"

class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	void setRenderer(SDL_Renderer* renderer) { gRenderer = renderer; }

	void addGameObject(GameObject* newGameObj);

	GameObject* getGameObject(size_t index);
	void getGameObjectList(GameObject** retList, size_t retListSize) const;

	void readInput(int input);
	void update();
	void renderScreen();

	void init(WindowScreen* windowScreen, TextureManager* textureManager);
	void close();

private:
	SDL_Renderer* gRenderer;

	GameObject** gameObjList;
	size_t gameObjListSize;
};

