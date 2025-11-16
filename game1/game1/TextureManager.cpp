#include "TextureManager.h"

SDL_Renderer* TextureManager::gRenderer = NULL;
std::vector<TextureManager::asset_t> TextureManager::assetList;

SDL_Texture* TextureManager::loadTexture(std::string path)
{
	//// Check Renderer
	//if (gRenderer == NULL) {
	//	return NULL;
	//}

	for (asset_t asset : assetList) {
		if (asset.path == path) return asset.texture;
	}

	SDL_Texture* newTexture = IMG_LoadTexture(gRenderer, path.c_str());
	if (newTexture == NULL) {
		GameErrors().SDL_IMG_PrintError("Unable to create texture from %s!", path.c_str());
	}
	
	asset_t newAsset = { path, newTexture };
	assetList.push_back(newAsset);

	return newTexture;
}

TextureManager::TextureManager()
{
	gRenderer = NULL;

	assetBasePath = "";
}

TextureManager::~TextureManager()
{
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
