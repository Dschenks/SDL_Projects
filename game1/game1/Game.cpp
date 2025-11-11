#include "game.h"
#include "WindowScreen.h"

Game::Game()
{
	isRunning = false;
	gWindow = NULL;
	gRenderer = NULL;

	gameStartTick = std::chrono::high_resolution_clock::time_point();
	lastFrameTick = std::chrono::milliseconds();

	frameRate = DEFAULT_FPS;
	frameMs = fps2ms(frameRate);

	WindowScreen().setScreenWidth(DEFAULT_SCREEN_WIDTH);
	WindowScreen().setScreenHeight(DEFAULT_SCREEN_HEIGHT);

	textureManager = NULL;

	gameScreen = NULL;
}

Game::Game(int screenWidth, int screenHeight) : Game()
{
	WindowScreen().setScreenWidth(screenWidth);
	WindowScreen().setScreenHeight(screenHeight);
}

Game::~Game()
{
}

int Game::_init_SDL()
{
	int ret = 0;

	if ((ret = SDL_Init(SDL_INIT_VIDEO)) < 0) {
		GameErrors().SDL_PrintError("SDL could not initialize! SDL Error: %s\n");
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
		GameErrors().SDL_IMG_PrintError("SDL_image could not initialize!");
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
	gWindow = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowScreen().getScreenWidth(), WindowScreen().getScreenHeight(), SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		GameErrors().SDL_PrintError("Window could not be created!");
		return -1;
	}
	// Setup Renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL) {
		GameErrors().SDL_PrintError("Renderer could not be created!");
		return false;
	}

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	// Setup SDL Image
	if ((ret = _init_SDL_IMG()) < 0) return ret;

	// Init Texture Manager
	this->textureManager = new TextureManager;
	textureManager->setRenderer(gRenderer);

	// Init frame clocks
	gameStartTick = std::chrono::high_resolution_clock::now();
	lastFrameTick = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - gameStartTick);

	isRunning = true;

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
	gameScreen->close();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	gRenderer = NULL;
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

std::chrono::milliseconds Game::fps2ms(Game::fps fps)
{
	return std::chrono::milliseconds((1000 / fps));
}

void Game::setFrameRate(Game::fps fps)
{
	if (fps > 200) return;

	frameRate = fps;
	frameMs = fps2ms(fps);
}

std::chrono::milliseconds Game::getCurrentTick() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - gameStartTick);
	// return std::chrono::milliseconds();
}

bool Game::tick()
{
	if (!isRunning) return false;

	std::chrono::milliseconds currentTick = getCurrentTick();
	if ((currentTick - lastFrameTick) > frameMs) {
		readInput();
		update();
		renderFrame();
		lastFrameTick = currentTick;
	}

	return true;
}

void Game::mainLoop() {
	while (isRunning) {
		std::chrono::milliseconds currentTick = getCurrentTick();
		if ((currentTick - lastFrameTick) > frameMs) {
			readInput();
			update();
			renderFrame();
			lastFrameTick = currentTick;
		}
	}
}

void Game::readInput()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event) != 0) {
		SDL_Keycode keyPressed = SDLK_UNKNOWN;

		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				gameScreen->readInput(GameTypes::MOVE_DIR_UP);
				break;
			case SDLK_RIGHT:
				gameScreen->readInput(GameTypes::MOVE_DIR_RIGHT);
				break;
			case SDLK_DOWN:
				gameScreen->readInput(GameTypes::MOVE_DIR_DOWN);
				break;
			case SDLK_LEFT:
				//keyPressed = (SDL_KeyCode)event.key.keysym.sym;
				gameScreen->readInput(GameTypes::MOVE_DIR_LEFT);
				break;
			default: break;
			}

			break;
		}
		default: break;
		}
	}
}

void Game::update()
{
}

void Game::renderFrame()
{
	SDL_RenderClear(gRenderer);
	// ADD STUFF TO RENDER WITH PAINTER'S ALGO
	gameScreen->renderScreen();

	SDL_RenderPresent(gRenderer);
}

void Game::setCurrentScreen(GameScreen* gameScreen)
{
	if (this->gameScreen != NULL) this->gameScreen->close();
	this->gameScreen = gameScreen;
	this->gameScreen->init(&windowScreen, textureManager);
}
