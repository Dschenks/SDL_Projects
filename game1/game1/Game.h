#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <time.h>
#include <chrono>
#include "TextureManager.h"
#include "GameErrors.h"
#include "GameScreen.h"
#include "GameTypes.h"
#include "gameTime.h"

using fps = GameTime::fps;

class Game
{
public:
	// Class Constructors
	Game();
	Game(int screenWidth, int screenHeight);
	~Game();

	// Object Setup
	int init();
	void close();

	// Renderer/Texture Methods
	SDL_Renderer* getRenderer() const { return gRenderer; }
	void setBaseAssetPath(std::string path) { textureManager->setAssetBasePath(path); }

	// Game Tick and core Loop functions
	bool tick();
	void mainLoop();
	GameTime* getGameClock() const { return gameClock; }

	void readInput();
	void update();
	void renderFrame();

	// Game Screen Methods
	void setCurrentScreen(GameScreen* gameScreen);

private:
	// SDL Initialization
	int _init_SDL();
	int _init_SDL_IMG();

	// Screen Window Size Data Class
	static const int DEFAULT_SCREEN_WIDTH = 640;
	static const int DEFAULT_SCREEN_HEIGHT = 480;
	WindowScreen windowScreen;

	// Global Game Display Objects
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	TextureManager* textureManager;
	GameScreen* gameScreen;				// Current game screen that holds all game screen objects e.g. players, enemies, tiles

	// Game Clock
	GameTime* gameClock;

	// Game State Variables
	bool isRunning;		// Boolean that reflects the game running state
};

