#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdarg>

// SCREEN DIMENSION CONSTANTS
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

std::string assetsDir = "C:\\Users\\dento\\source\\repos\\SDL_projects\\assets\\";

bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture( std::string path );

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

std::string _SDL_FormatErrorMsg(std::string errorMsgFmt, std::string errorMsg) {
	if (errorMsg == "") return "\n";	// If the return string is nothing, don't return a message

	// Create temp C char string to format with the SDL Error Message
	size_t tempStrSize = errorMsg.size() + errorMsgFmt.size();
	char* tempStr = new char[tempStrSize];

	int c = snprintf(tempStr, tempStrSize, errorMsgFmt.c_str(), errorMsg.c_str());
	
	errorMsg = tempStr;		// swap temp with returned string
	delete[] tempStr;		// cleanup temp string
	
	return errorMsg;
}

void SDL_PrintError(std::string fmt...) {
	fmt.append(_SDL_FormatErrorMsg(" SDL Error: %s\n", SDL_GetError()));
	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt.c_str(), args);
	va_end(args);
}

void SDL_IMG_PrintError(std::string fmt...) {
	fmt.append(_SDL_FormatErrorMsg(" SDL_image Error: %s\n", IMG_GetError()));
	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt.c_str(), args);
	va_end(args);
}

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_PrintError("SDL could not initialize! SDL Error: %s\n");
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}

	gWindow = SDL_CreateWindow("GAME 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		SDL_PrintError("Window could not be created!");
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL) {
		SDL_PrintError("Renderer could not be created!");
		return false;
	}

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

	int imagFlags = IMG_INIT_PNG;
	if ( !(IMG_Init(imagFlags) & imagFlags) ) {
		SDL_IMG_PrintError("SDL_image could not initialize!");
		return false;
	}

	return true;
}

bool loadMedia() {
	// Load PNG picture
	gTexture = loadTexture(assetsDir.append("red_face_50_50.png"));
	if (gTexture == NULL) {
		printf("Failed to load texture image!\n");
		return false;
	}
	return true;
}

void close() {
	// Free loaded image
	SDL_DestroyTexture(gTexture);

	// Destroy Window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path) {
	SDL_Texture* newTexture = IMG_LoadTexture(gRenderer, path.c_str());
	if (newTexture == NULL) {
		SDL_IMG_PrintError("Unable to create texture from %s!", path.c_str());
	}
	return newTexture;
}

int main(int agrc, char* args[]) {
	bool init_f = true;
	if (!( init_f &= init() )) printf("Failed to initialize!\n");
	if (!( init_f &= loadMedia() )) printf("Failed to Load Media!\n");
	
	if (init_f) {
		bool quit = false;

		SDL_Event e;

		int x = (SCREEN_WIDTH / 2), y = (SCREEN_HEIGHT / 2);
		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				SDL_Keycode keyPressed = SDLK_UNKNOWN;
				switch (e.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym) {
					case SDLK_UP:
					case SDLK_RIGHT:
					case SDLK_DOWN:
					case SDLK_LEFT:
						keyPressed = (SDL_Keycode)e.key.keysym.sym;
						break;
					default: break;
					}
					break;
				default: break;
				}

				SDL_RenderClear(gRenderer);

				int w, h;
				SDL_Rect* rect;
				if (SDL_QueryTexture(gTexture, NULL, NULL, &w, &h) < 0) {
					SDL_PrintError("Could not query texture attributes!");
					rect = new SDL_Rect;
				}
				else {
					switch (keyPressed) {
					case SDLK_UP:
						y-=4;
						if (y - h/2 < 0) y = 0 + h/2;
						break;
					case SDLK_RIGHT:
						x+=4;
						if (x + w / 2 >= SCREEN_WIDTH) x = SCREEN_WIDTH - w / 2;
						break;
					case SDLK_DOWN:
						y+=4;
						if (y + h/2 >= SCREEN_HEIGHT) y = SCREEN_HEIGHT - h/2;
						break;
					case SDLK_LEFT:
						x-=4;
						if (x - w / 2 < 0) x = 0 + w / 2;
						break;
					}
					rect = new SDL_Rect { x - (w / 2), y - (h / 2), w, h };
				}

				SDL_RenderCopy(gRenderer, gTexture, NULL, rect);

				SDL_RenderPresent(gRenderer);
				delete rect;
			}
		}
	}
	
	//Free resources and close SDL
	close();

	return 0;
}