#include "GameMap.h"
#include <cassert>

using tileID = GameMap::tileID;

GameMap::GameMap() :
	initCallback(this, &GameMap::init),
	renderCallback(this, &GameMap::render)
{
	GameObjectCallbacks* callbacks = gameObject.getGameObjCallbacks();
	callbacks->setInitCallback(initCallback);
	callbacks->setRenderCallback(renderCallback);

	gRenderer = nullptr;
	windowScreen = nullptr;
	textureManager = nullptr;

	mapWidth = DEFAULT_MAP_WIDTH;
	mapHeight = DEFAULT_MAP_HEIGHT;
	resizeMap(0, 0);
}

tileID GameMap::addTileSprite(std::string path, SDL_Rect srcrect)
{
	tilePaths.push_back(path);
	tileSrcrects.push_back(srcrect);
	return (tileID)(tilePaths.size() - 1);
}

void GameMap::setTile(int x, int y, tileID tileID)
{
	//assert(x > mapWidth || x < 0 || y > mapHeight || y < 0);
	if (x > mapWidth || x < 0 || y > mapHeight || y < 0) return;

	tileMap[x][y] = tileID;
}

void GameMap::setTileSize(int w, int h)
{
	dstrect.w = w; 
	dstrect.h = h;
}

void GameMap::setMapWidth(int width)
{
	int t = mapWidth;
	mapWidth = width;
	resizeMap(t, mapHeight);
}

void GameMap::setMapHeight(int height)
{
	int t = mapHeight;
	mapHeight = height;
	resizeMap(mapWidth, t);
}

void GameMap::init(WindowScreen* windowScreen, TextureManager* textureManager)
{
	this->windowScreen = windowScreen;
	this->textureManager = textureManager;
	gRenderer = textureManager->getRenderer();

	loadMedia();
}

void GameMap::render()
{
	SDL_Rect srcrect = { 0 };

	for (int width = 0; width < mapWidth; width++) {
		dstrect.x = dstrect.w * width;
		for (int height = 0; height < mapHeight; height++) {
			dstrect.y = dstrect.h * height;
			SDL_RenderCopy(gRenderer, 
				tileTextures[tileMap[width][height]], 
				&tileSrcrects[tileMap[width][height]], 
				&dstrect);
		}
	}
}

void GameMap::loadMedia()
{
	SDL_Texture* t;
	for (int i = 0; i < tilePaths.size(); i++) {
		std::string path = tilePaths[i];

		if ((t = textureManager->loadAssetTexture(path)) == nullptr) {
			printf("No asset texture found for Map Tile %s!\n", path.c_str());
			//return UINT16_MAX;
		}
		tileTextures.push_back(t);
	}
}

void GameMap::resizeMap(int oldWidth, int oldHeight)
{
	tileID** t;
	t = new tileID * [mapWidth];
	for (int i = 0; i < mapWidth; i++) t[i] = new tileID[mapHeight];

	for (int i = 0; i < mapWidth; i++) memset(t[i], 0, sizeof(tileID) * mapHeight);

	int cpyWidth = (oldWidth < mapWidth) ? oldWidth : mapWidth;
	int cpyHeight = (oldHeight < mapHeight) ? oldHeight : mapHeight;
	for (int i = 0; i < cpyWidth; i++) {
		for (int j = 0; j < cpyHeight; j++) {
			t[i][j] = tileMap[i][j];
		}
	}

	for (int i = 0; i < oldWidth; i++) delete[] tileMap[i];
	delete[] tileMap;

	tileMap = t;
}
