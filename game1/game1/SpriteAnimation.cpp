#include "SpriteAnimation.h"

using ms = GameTime::ms;

SpriteAnimation::SpriteAnimation()
{
	animationGameClock = new GameTime;
}

SpriteAnimation::~SpriteAnimation()
{
	delete animationGameClock;
}

void SpriteAnimation::init()
{
	animationGameClock->init();
}

SpriteAnimation::spriteAnimationID SpriteAnimation::addAnimationSprite(sprite spriteMod)
{
	initSpriteMod(&spriteMod);
	spriteList.push_back(spriteMod);
	return (SpriteAnimation::spriteAnimationID)spriteList.size() - 1;
}

sprite* SpriteAnimation::getAnimationSprite(spriteAnimationID id)
{
	if (id >= spriteList.size()) return nullptr;
	return &spriteList.at(id);
}

void SpriteAnimation::setFlip(SDL_RendererFlip flip)
{
	for (int i = 0; i < spriteList.size(); i++) spriteList[i].flip = flip;
}

void SpriteAnimation::restartAnimation()
{
	animationGameClock->resetClock();
}

void SpriteAnimation::tick(sprite* &modifiers)
{
	if (animationGameClock->checkNewFrameTick()) {
		animationGameClock->updateFrameTime();
	}

	size_t animationFrame = animationGameClock->getFrameCount() % spriteList.size();
	modifiers = &(spriteList[animationFrame]);
}

void SpriteAnimation::initSpriteMod(sprite* spriteMod)
{
	if (!spriteMod->gTextureSet) {
		spriteMod->gTexture = nullptr;
		spriteMod->gTextureSet = true;
	}
	if (!spriteMod->srcRectSet) {
		spriteMod->srcRect.w = 5;
		spriteMod->srcRect.h = 5;
		spriteMod->srcRect.x = 5;
		spriteMod->srcRect.y = 5;
		spriteMod->srcRectSet = true;
	}
	if (!spriteMod->rotationSet) {
		spriteMod->rotation = 0;
		spriteMod->rotationSet = true;
	}
	if (!spriteMod->flipSet) {
		spriteMod->flip = SDL_FLIP_NONE;
		spriteMod->flipSet = true;
	}
	if (!spriteMod->alphaSet) spriteMod->alpha = 0xFF;
	if (!spriteMod->scaleSet) spriteMod->scale = 1;
}
