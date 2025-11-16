#pragma once
#include "GameObject.h"
#include "TextureManager.h"
#include "GameTypes.h"
#include <SDL.h>
#include "gameTime.h"
#include "SpriteAnimation.h"

using spriteModifier_t = SpriteTypes::spriteAssetModifiers_t;

class Player
{
public:
	// Class Constructors
	Player();

	// SDL Display and Game Engine Methods
	void setWindowScreen(WindowScreen* windowScreen) { this->windowScreen = windowScreen; }
	void setRenderer(SDL_Renderer* renderer) { this->gRenderer = renderer; }
	void setTextureManager(TextureManager* textureManager) { this->textureManager = textureManager; }
	void setGameClock(GameTime* gameClock) { this->gameClock = gameClock; }

	// Game Object Methods
	GameObject* getGameObject() const { return (GameObject*)&gameObj; }

	// Asset Sprite Methods
	void setSpriteTexure(std::string path, uint32_t spriteAssetFlag);
	void addSpriteFrame(uint32_t spriteAssetFlag, spriteModifier_t spriteMod);
	void setSpriteFps(uint32_t spriteAssetFlag, fps fps);
	
	// Global Sprite Modifiers
	void setScale(int scale);
	void setSpeed(GameTypes::ftps speed);

	// Game Engine Callback Methods
	void init(WindowScreen* windowScreen, TextureManager* textureManager);
	void close();
	void tick();
	void render();
	void move(GameTypes::move_dir_t moveDir);

private:

	int loadMedia();
	void initSprites();
	// Game Object Object
	GameObject gameObj;

	// Game Engine Callbacks
	Callback<Player, WindowScreen*, TextureManager*> initCallback;
	Callback<Player> closeCallback;
	Callback<Player> tickCallback;
	Callback<Player> renderCallback;
	Callback<Player, GameTypes::move_dir_t> moveCallback;

	// SDL Display and Game Engine Variables
	SDL_Renderer* gRenderer;
	WindowScreen* windowScreen;
	TextureManager* textureManager;
	GameTime* gameClock;

	// Asset Sprite Variables
	static const uint32_t spriteAssetSupport = {
		SpriteTypes::SPRITE_STANDING | SpriteTypes::SPRITE_RUNNING_RIGHT
	};
	static const uint8_t numSpriteAssetSupport;
	static const uint8_t getNumSpriteAssetFlags(uint32_t flags) {
		uint8_t c = 0;
		for (uint32_t i = 0; i < 32; i++) if ((1 << i) & spriteAssetSupport) c++;
		return c;
	}

	std::string* spritePaths;
	SDL_Texture** spriteTextures;
	SpriteAnimation* spriteAnimations;

	spriteModifier_t* frameSprite;

	// Movement State Variables
	GameTypes::move_dir_t lastMovement;
	bool playerMoved;
	bool facingRight;
	GameTypes::movementSpeed_t playerSpeed;
	GameTime* movementClock;

	uint16_t globalScaling;

	// Asset Rendering Blocks
	SDL_Rect* srcRect;		// points to a source rectangle from an animation object
	SDL_Rect destRect;		// sets the render point
};








/*
int w, h;
if (SDL_QueryTexture(gTexture, NULL, NULL, &w, &h) < 0) {
	GameErrors::SDL_PrintError("Could not query texture attributes!\n");
	return;
}
*/
//destRect.w = w * scaleUp;
//destRect.h = h * scaleUp;
//destRect.x = (windowScreen->getScreenWidth() / 2) - (w / 2);
//destRect.y = (windowScreen->getScreenHeight() / 2) - (h / 2);


