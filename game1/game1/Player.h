#pragma once
#include "GameObject.h"
#include "TextureManager.h"
#include "GameTypes.h"
#include <SDL.h>
class Player
{
public:
	Player();

	//void setGame(Game* game) { this->game = game; }
	void setWindowScreen(WindowScreen* windowScreen) { this->windowScreen = windowScreen; }
	void setRenderer(SDL_Renderer* renderer) { this->gRenderer = renderer; }
	void setTextureManager(TextureManager* textureManager) { this->textureManager = textureManager; }

	GameObject* getGameObject() const { return (GameObject*)&gameObj; }

	void setSprite(std::string path, uint32_t spriteAssetFlag);

	void setScaleUp(int scale) { scaleUp = scale; }

	void init(WindowScreen* windowScreen, TextureManager* textureManager);
	void close();
	void tick();
	void render();
	void move(GameTypes::move_dir_t moveDir);
private:
	int loadMedia(std::string path);

	WindowScreen* windowScreen;

	GameObject gameObj;

	Callback<Player, WindowScreen*, TextureManager*> initCallback;
	Callback<Player> closeCallback;
	Callback<Player> tickCallback;
	Callback<Player> renderCallback;
	Callback<Player, GameTypes::move_dir_t> moveCallback;

	SDL_Renderer* gRenderer;
	TextureManager* textureManager;

	static const uint32_t spriteAssetSupport = (
			SpriteTypes::SPRITE_STANDING_1 |
			SpriteTypes::SPRITE_STANDING_2 |
			SpriteTypes::SPRITE_RUNNING_LEFT_1 |
			SpriteTypes::SPRITE_RUNNING_LEFT_2
		);

	std::string spriteStanding1Path;
	std::string spriteStanding2Path;
	std::string spriteRunningLeft1Path;
	std::string spriteRunningLeft2Path;

	GameTypes::move_dir_t lastMovement;
	bool playerMoved;

	int scaleUp;

	SDL_Texture* gTexture;
	SDL_Rect srcRect, destRect;
};

