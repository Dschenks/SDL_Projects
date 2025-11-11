#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture* loadTexture(std::string path);

	TextureManager();

	void setAssetBasePath(std::string path);
	std::string getAssetBasePath() const { return assetBasePath; };

	SDL_Texture* loadAssetTexture(std::string fileName);
private:
	static SDL_Renderer* gRenderer;

	std::string assetBasePath;

	std::string* pathList;
	SDL_Texture* textureList;
	size_t textureListSize;
};

