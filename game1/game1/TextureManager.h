#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "GameErrors.h"
#include <vector>

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
	typedef struct {
		std::string path;
		SDL_Texture* texture;
	} asset_t;

	static SDL_Renderer* gRenderer;

	std::string assetBasePath;

	static std::vector<asset_t> assetList;
};

