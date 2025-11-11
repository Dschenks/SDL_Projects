#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(std::string path)
{
	// Check Renderer
	//if (gRenderer == NULL) {

	//}

	SDL_Texture* newTexture = IMG_LoadTexture(gRenderer, path.c_str());
	if (newTexture == NULL) {
		Game().SDL_IMG_PrintError("Unable to create texture from %s!", path.c_str());
	}
	return newTexture;
}

TextureManager::TextureManager()
{
	gRenderer = NULL;

	assetBasePath = "";

	pathList = NULL;
	textureList = NULL;
	textureListSize = 0;
}

void TextureManager::setAssetBasePath(std::string path)
{
	assetBasePath = path;
	// TODO: Verify this is a real path
}

SDL_Texture* TextureManager::loadAssetTexture(std::string fileName)
{
	std::string s = assetBasePath;
	return loadTexture(s.append(fileName));
}
