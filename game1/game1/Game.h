#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <time.h>
#include <chrono>
#include "TextureManager.h"

class Game
{
public:
	Game();
	Game(int screenWidth, int screenHeight);
	~Game();

	int init();
	void close();

	void setFrameRate();
	int getFrameRate();

	std::chrono::milliseconds getCurrentTick() const;
	void tick();

	void readInput();
	void update();
	void renderFrame();

	static void SDL_IMG_PrintError(std::string fmt...);
	static void SDL_PrintError(std::string fmt...);

private:
	int _init_SDL();
	int _init_SDL_IMG();

	static std::string _SDL_FormatErrorMsg(std::string errorMsgFmt, std::string errorMsg);

	static const int DEFAULT_SCREEN_WIDTH = 640;
	static const int DEFAULT_SCREEN_HEIGHT = 480;

	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	TextureManager* TextureManager;


	std::chrono::high_resolution_clock::time_point gameStartTick;
	std::chrono::milliseconds lastFrameTick;

	bool isRunning;

	int screenWidth;
	int screenHeight;
};

