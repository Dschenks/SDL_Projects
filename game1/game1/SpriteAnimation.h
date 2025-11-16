#pragma once
#include "gameTime.h"
#include "GameTypes.h"
#include <SDL.h>
#include <vector>

using fps = GameTime::fps;
using ms = GameTime::ms;
using sprite = SpriteTypes::spriteAssetModifiers_t;

class SpriteAnimation
{
public:
	typedef uint16_t spriteAnimationID;

	SpriteAnimation();
	~SpriteAnimation();

	void init();

	spriteAnimationID addAnimationSprite(sprite spriteMod);
	void setAnimationFps(fps fps) { animationGameClock->setFrameRate(fps); }

	size_t getNumAnimationSprites() const { return spriteList.size(); }
	sprite* getAnimationSprite(spriteAnimationID id=0);

	// Global animation modifiers
	void setFlip(SDL_RendererFlip flip);

	void restartAnimation();
	void tick(sprite* &modifiers);

private:
	void initSpriteMod(sprite* spriteMod);

	GameTime* animationGameClock;
	std::vector <sprite> spriteList;
};

