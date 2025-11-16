#include "player.h"
#include "GameErrors.h"
#include "GameObjectCallbacks.h"
#include "GameTypes.h"
#include <stdio.h>
#include <cassert>

const uint8_t Player::numSpriteAssetSupport = getNumSpriteAssetFlags(spriteAssetSupport);

Player::Player() :
	initCallback(this, &Player::init), 
	closeCallback(this, &Player::close), 
	tickCallback(this, &Player::tick), 
	renderCallback(this, &Player::render), 
	moveCallback(this, &Player::move)
{
	// Initailize the game engine object callbacks
	GameObjectCallbacks* callbacks = gameObj.getGameObjCallbacks();
	callbacks->setInitCallback(initCallback);
	callbacks->setCloseCallback(closeCallback);
	callbacks->setTickCallback(tickCallback);
	callbacks->setRenderCallback(renderCallback);
	callbacks->setMoveCallback(moveCallback);

	gRenderer = nullptr;
	windowScreen = nullptr;
	textureManager = nullptr;
	gameClock = nullptr;

	spritePaths = new std::string[numSpriteAssetSupport];
	spriteTextures = new SDL_Texture * [numSpriteAssetSupport];
	for (int i = 0; i < numSpriteAssetSupport; i++) spriteTextures[i] = nullptr;
	spriteAnimations = new SpriteAnimation[numSpriteAssetSupport];

	frameSprite = nullptr;

	lastMovement = GameTypes::MOVE_DIR_NONE;
	playerMoved = false;
	facingRight = true;
	playerSpeed.ftps = GameTypes::DEFAULT_PLAYER_SPEED;
	playerSpeed.pps = GameTypes::speed2pps(playerSpeed.ftps);
	movementClock = new GameTime;
	movementClock->setFrameRate(playerSpeed.pps);

	globalScaling = 1;

	srcRect = nullptr;
	destRect = { 0 };
}

void Player::setSpriteTexure(std::string path, uint32_t spriteAssetFlag)
{
	if (!SpriteTypes::checkFlagSupported(spriteAssetSupport, spriteAssetFlag)) return; //return nullptr;

	uint8_t spriteIndex = SpriteTypes::flag2index(spriteAssetSupport, spriteAssetFlag);

	spritePaths[spriteIndex] = path;
}

void Player::addSpriteFrame(uint32_t spriteAssetFlag, spriteModifier_t spriteMod)
{
	uint8_t spriteIndex = SpriteTypes::flag2index(spriteAssetSupport, spriteAssetFlag);

	spriteMod.gTextureSet = true;
	spriteAnimations[spriteIndex].addAnimationSprite(spriteMod);
}

void Player::setSpriteFps(uint32_t spriteAssetFlag, fps fps)
{
	uint8_t spriteIndex = SpriteTypes::flag2index(spriteAssetSupport, spriteAssetFlag);
	spriteAnimations[spriteIndex].setAnimationFps(fps);
}

void Player::setScale(int scale)
{
	globalScaling = scale;	// tied to speed
	//setSpeed(playerSpeed.ftps);
}

void Player::setSpeed(GameTypes::ftps speed)
{
	playerSpeed.ftps = speed * globalScaling;
	playerSpeed.pps = GameTypes::speed2pps(playerSpeed.ftps);
	movementClock->setFrameRate(playerSpeed.pps);
}

void Player::init(WindowScreen* windowScreen, TextureManager* textureManager)
{
	// Setup display objects
	setWindowScreen(windowScreen);
	this->textureManager = textureManager;
	setRenderer(textureManager->getRenderer());

	if (loadMedia() < 0) {
		printf("Failed to initialize Player Class!\n");
		return;
	}

	uint8_t spriteIndex = SpriteTypes::flag2index(spriteAssetSupport, SpriteTypes::SPRITE_STANDING);
	SpriteAnimation* spriteAction = &spriteAnimations[spriteIndex];
	spriteAction->restartAnimation();
	SDL_Rect srcRect = spriteAction->getAnimationSprite()->srcRect;
	
	destRect.w = srcRect.w * spriteAction->getAnimationSprite()->scale * globalScaling;
	destRect.h = srcRect.h * spriteAction->getAnimationSprite()->scale * globalScaling;
	destRect.x = (windowScreen->getScreenWidth() / 2) - (destRect.w / 2);
	destRect.y = (windowScreen->getScreenHeight() / 2) - (destRect.h / 2);

	initSprites();
}

void Player::close()
{
	//SDL_DestroyTexture(gTexture);
}

void Player::tick()
{
	// Nothing todo yet
}

void Player::render()
{
	if (playerMoved == false) {
		uint8_t spriteIndex = SpriteTypes::flag2index(spriteAssetSupport, SpriteTypes::SPRITE_STANDING);
		SpriteAnimation* spriteAction = &spriteAnimations[spriteIndex];
		
		if (lastMovement != GameTypes::MOVE_DIR_NONE) spriteAction->restartAnimation();

		spriteAction->tick(frameSprite);
		lastMovement = GameTypes::MOVE_DIR_NONE;
	}
	playerMoved = false;

	assert(frameSprite != nullptr);

	destRect.w = frameSprite->srcRect.w * frameSprite->scale * globalScaling;
	destRect.h = frameSprite->srcRect.h * frameSprite->scale * globalScaling;

	SDL_RendererFlip flip = facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	//SDL_RenderCopy(gRenderer, gTexture, NULL, &destRect);
	SDL_RenderCopyEx(gRenderer, frameSprite->gTexture, &frameSprite->srcRect, &destRect, frameSprite->rotation, NULL, flip);
}

void Player::move(GameTypes::move_dir_t moveDir)
{
	SpriteAnimation* spriteAction = nullptr;
	SpriteTypes::spriteAssetFlags_t spriteFlag = SpriteTypes::SPRITE_RUNNING_RIGHT;
	static int xMove = 0;
	static int yMove = 0;
	int movAmt = globalScaling;

	switch (moveDir) {
	case GameTypes::MOVE_DIR_UP:
		yMove -= movAmt;
		break;
	case GameTypes::MOVE_DIR_DOWN:
		yMove += movAmt;
		break;
	case GameTypes::MOVE_DIR_RIGHT:
		facingRight = true;
		xMove += movAmt;
		break;
	case GameTypes::MOVE_DIR_LEFT:
		facingRight = false;
		xMove -= movAmt;
		break;
	default: 
		spriteFlag = SpriteTypes::SPRITE_STANDING;
		break;
	}
	uint8_t spriteIndex = SpriteTypes::flag2index(spriteAssetSupport, spriteFlag);
	spriteAction = &spriteAnimations[spriteIndex];

	if (lastMovement == GameTypes::MOVE_DIR_NONE) {
		movementClock->resetClock();
		spriteAction->restartAnimation();
		xMove = 0;
		yMove = 0;
	}

	spriteAction->tick(frameSprite);

	lastMovement = moveDir;
	playerMoved = true;

	if (!movementClock->checkNewFrameTick()) return;
	destRect.x += xMove;
	destRect.y += yMove;
	movementClock->updateFrameTime();

	xMove = 0;
	yMove = 0;
}

int Player::loadMedia()
{
	for (int i = 0; i < numSpriteAssetSupport; i++) {
		std::string path = spritePaths[i];
		
		if (path == "") continue;

		if ((spriteTextures[i] = textureManager->loadAssetTexture(path)) == nullptr) {
			printf("No asset texture found for Player Object %s sprite!\n", SpriteTypes::flagStrings[i].c_str());
			return -1;
		}

		size_t numSprites = spriteAnimations[i].getNumAnimationSprites();
		for (int k = 0; k < numSprites; k++) spriteAnimations[i].getAnimationSprite(k)->gTexture = spriteTextures[i];
	}

	return 0;
}

void Player::initSprites()
{
	for (int i = 0; i < numSpriteAssetSupport; i++) {
		spriteAnimations[i].init();
	}
}
