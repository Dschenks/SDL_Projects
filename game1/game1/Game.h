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

class Game
{
public:
	typedef uint16_t fps;

	Game();
	Game(int screenWidth, int screenHeight);
	~Game();

	int init();
	void close();

	SDL_Renderer* getRenderer() const { return gRenderer; }
	void setBaseAssetPath(std::string path) { textureManager->setAssetBasePath(path); }

	void setFrameRate(fps fps);
	fps getFrameRate() const { return frameRate; }

	std::chrono::milliseconds getCurrentTick() const;
	bool tick();

	void mainLoop();

	void readInput();
	void update();
	void renderFrame();

	void setCurrentScreen(GameScreen* gameScreen);

	static std::chrono::milliseconds fps2ms(Game::fps fps);

private:
	int _init_SDL();
	int _init_SDL_IMG();

	static const int DEFAULT_SCREEN_WIDTH = 640;
	static const int DEFAULT_SCREEN_HEIGHT = 480;
	WindowScreen windowScreen;

	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	TextureManager* textureManager;

	std::chrono::high_resolution_clock::time_point gameStartTick;
	std::chrono::milliseconds lastFrameTick;

	static const fps DEFAULT_FPS = 30;

	fps frameRate;
	std::chrono::milliseconds frameMs;

	bool isRunning;

	GameScreen* gameScreen;
};

