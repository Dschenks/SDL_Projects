#include "game.h"

Game::Game()
{
	isRunning = false;
	gWindow = NULL;
	gRenderer = NULL;

	gameStartTick = std::chrono::high_resolution_clock::time_point();
	lastFrameTick = std::chrono::milliseconds();

	screenWidth = DEFAULT_SCREEN_WIDTH;
	screenHeight = DEFAULT_SCREEN_HEIGHT;

	TextureManager = NULL;
}

Game::Game(int screenWidth, int screenHeight) : Game()
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	TextureManager = NULL;
}

Game::~Game()
{
}

int Game::_init_SDL()
{
	int ret = 0;

	if ((ret = SDL_Init(SDL_INIT_VIDEO)) < 0) {
		SDL_PrintError("SDL could not initialize! SDL Error: %s\n");
		return ret;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}

	return ret;
}

int Game::_init_SDL_IMG()
{
	int ret = 0;

	int imagFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imagFlags) & imagFlags)) {
		SDL_IMG_PrintError("SDL_image could not initialize!");
		return -1;
	}

	return ret;
}

int Game::init()
{
	int ret = 0;
	// SDL init
	if ((ret = _init_SDL()) < 0) return ret;
	// Setup window
	gWindow = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		SDL_PrintError("Window could not be created!");
		return -1;
	}
	// Setup Renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL) {
		SDL_PrintError("Renderer could not be created!");
		return false;
	}

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	// Setup SDL Image
	if ((ret = _init_SDL_IMG()) < 0) return ret;

	// Init Texture Manager
	this->TextureManager = new TextureManager();

	return ret;
}

void Game::close()
{
	/**
	* 1. Destroy Textures and surfaces not spawned from window
	* 2. Destroy Renderer
	* 3. Destroy Window
	* 4. NULL pointers
	* 5. Quit IMG
	* 6. Quit SDL
	*/
	// Destroy Textures

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	gRenderer = NULL;
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

void Game::setFrameRate()
{
}

int Game::getFrameRate()
{
	return 0;
}

std::chrono::milliseconds Game::getCurrentTick() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - gameStartTick);
	// return std::chrono::milliseconds();
}

void Game::tick()
{
}

void Game::readInput()
{
}

void Game::update()
{
}

void Game::renderFrame()
{
}

std::string Game::_SDL_FormatErrorMsg(std::string errorMsgFmt, std::string errorMsg)
{
	if (errorMsg == "") return "\n";	// If the return string is nothing, don't return a message

	// Create temp C char string to format with the SDL Error Message
	size_t tempStrSize = errorMsg.size() + errorMsgFmt.size();
	char* tempStr = new char[tempStrSize];

	int c = snprintf(tempStr, tempStrSize, errorMsgFmt.c_str(), errorMsg.c_str());

	errorMsg = tempStr;		// swap temp with returned string
	delete[] tempStr;		// cleanup temp string

	return errorMsg;
}

void Game::SDL_IMG_PrintError(std::string fmt ...)
{
	fmt.append(_SDL_FormatErrorMsg(" SDL_image Error: %s\n", IMG_GetError()));
	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt.c_str(), args);
	va_end(args);
}

void Game::SDL_PrintError(std::string fmt ...)
{
	fmt.append(_SDL_FormatErrorMsg(" SDL Error: %s\n", SDL_GetError()));
	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt.c_str(), args);
	va_end(args);
}
