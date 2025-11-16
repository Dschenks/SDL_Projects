#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "Callback.h"
#include "WindowScreen.h"
#include "TextureManager.h"
#include "GameObject.h"

class GameMap
{
public:
	typedef uint16_t tileID;

	static const int DEFAULT_MAP_WIDTH = 16;	// px
	static const int DEFAULT_MAP_HEIGHT = 16;	// px

	GameMap();

	tileID addTileSprite(std::string path, SDL_Rect srcrect);
	
	void setTile(int x, int y, tileID tileID);

	int getMapWidth() const { return mapWidth; }
	int getMapHeight() const { return mapHeight; }

	void setTileSize(int w, int h);

	void setMapWidth(int width);
	void setMapHeight(int height);

	void init(WindowScreen* windowScreen, TextureManager* textureManager);
	void render();
	GameObject gameObject;
private:
	void loadMedia();
	void resizeMap(int oldWidth, int oldHeight);



	Callback<GameMap, WindowScreen*, TextureManager*> initCallback;
	Callback<GameMap> renderCallback;

	SDL_Renderer* gRenderer;
	WindowScreen* windowScreen;
	TextureManager* textureManager;

	std::vector <std::string> tilePaths;
	std::vector <SDL_Texture*> tileTextures;
	std::vector <SDL_Rect> tileSrcrects;

	int mapWidth;
	int mapHeight;
	
	SDL_Rect dstrect;

	tileID** tileMap;
};

