#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "GameErrors.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	static SDL_Texture* loadTexture(std::string path);
	static void setRenderer(SDL_Renderer* renderer) { gRenderer = renderer; }
	static SDL_Renderer* getRenderer() { return gRenderer; }

	void setAssetBasePath(std::string path);
	std::string getAssetBasePath() const { return assetBasePath; }

	SDL_Texture* loadAssetTexture(std::string fileName);
private:
	static SDL_Renderer* gRenderer;

	std::string assetBasePath;

	std::string* pathList;
	SDL_Texture* textureList;
	size_t textureListSize;
};

