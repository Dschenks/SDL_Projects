#include "player.h"
#include "GameErrors.h"
#include "GameObjectCallbacks.h"
#include "GameTypes.h"
#include <stdio.h>

Player::Player() :
	initCallback(this, &Player::init), closeCallback(this, &Player::close), tickCallback(this, &Player::tick), renderCallback(this, &Player::render), moveCallback(this, &Player::move)
{
	GameObjectCallbacks* callbacks = gameObj.getGameObjCallbacks();
	callbacks->setInitCallback(initCallback);
	callbacks->setCloseCallback(closeCallback);
	callbacks->setTickCallback(tickCallback);
	callbacks->setRenderCallback(renderCallback);
	callbacks->setMoveCallback(moveCallback);

	srcRect = SDL_Rect();
	destRect = SDL_Rect();

	gRenderer = NULL;
	gTexture = NULL;
	textureManager = NULL;
	windowScreen = NULL;

	lastMovement = GameTypes::MOVE_DIR_NONE;
	playerMoved = false;

	spriteStanding1Path = "";
	spriteStanding2Path = "";
	spriteRunningLeft1Path = "";
	spriteRunningLeft2Path = "";

	scaleUp = 1;

	rotation = 0;
	flipType = SDL_FLIP_NONE;
}

void Player::setSprite(std::string path, uint32_t spriteAssetFlag)
{
	switch (spriteAssetFlag) {
	case SpriteTypes::SPRITE_STANDING_1:
		spriteStanding1Path = path;
		break;
	case SpriteTypes::SPRITE_STANDING_2:
		spriteStanding2Path = path;
		break;
	case SpriteTypes::SPRITE_RUNNING_LEFT_1:
		spriteRunningLeft1Path = path;
		break;
	case SpriteTypes::SPRITE_RUNNING_LEFT_2:
		spriteRunningLeft2Path = path;
		break;
	default: break;
	}
}

void Player::init(WindowScreen* windowScreen, TextureManager* textureManager)
{
	//setGame(game);
	setWindowScreen(windowScreen);
	this->textureManager = textureManager;
	setRenderer(textureManager->getRenderer());

	if (loadMedia(spriteStanding1Path) < 0) {
		printf("Failed to initialize Player Class!\n");
		return;
	}

	int w, h;
	if (SDL_QueryTexture(gTexture, NULL, NULL, &w, &h) < 0) {
		GameErrors::SDL_PrintError("Could not query texture attributes!\n");
		return;
	}
	srcRect.w = w * scaleUp;
	srcRect.h = h * scaleUp;
	srcRect.x = (windowScreen->getScreenWidth() / 2) - (w / 2);
	srcRect.y = (windowScreen->getScreenHeight() / 2) - (h / 2);

	destRect = srcRect;
}

void Player::close()
{
	SDL_DestroyTexture(gTexture);
}

void Player::tick()
{
	// Nothing todo yet
}

void Player::render()
{
	static bool b = true;
	if (playerMoved == false) {
		if (lastMovement != GameTypes::MOVE_DIR_NONE) b = true;
		lastMovement = GameTypes::MOVE_DIR_NONE;
		
		if (b == true && spriteStanding1Path != "") {
			loadMedia(spriteStanding1Path);
			b = false;
		}
		else if (spriteStanding2Path != "") {
			loadMedia(spriteStanding2Path);
			b = true;
		}
	}
	playerMoved = false;

	//SDL_RenderCopy(gRenderer, gTexture, NULL, &destRect);
	SDL_RenderCopyEx(gRenderer, gTexture, NULL, &destRect, rotation, NULL, flipType);

	rotation = 0;
	flipType = SDL_FLIP_NONE;
}

void Player::move(GameTypes::move_dir_t moveDir)
{
	static bool b = true;
	switch (moveDir) {
	case GameTypes::MOVE_DIR_UP:
		destRect.y -= 4;
		break;
	case GameTypes::MOVE_DIR_DOWN:
		destRect.y += 4;
		break;
	case GameTypes::MOVE_DIR_RIGHT:
		if (b && lastMovement == GameTypes::MOVE_DIR_RIGHT) {
			if (spriteRunningLeft2Path != "") loadMedia(spriteRunningLeft2Path);
			b = false;
		}
		else {
			if (spriteRunningLeft1Path != "") loadMedia(spriteRunningLeft1Path);
			b = true;
		}

		destRect.x += (4 * scaleUp/4);
		flipType = SDL_FLIP_HORIZONTAL;

		break;
	case GameTypes::MOVE_DIR_LEFT:
		if (b && lastMovement == GameTypes::MOVE_DIR_LEFT) {
			if (spriteRunningLeft2Path != "") loadMedia(spriteRunningLeft2Path);
			b = false;
		} else {
			if (spriteRunningLeft1Path != "") loadMedia(spriteRunningLeft1Path);
			b = true;
		}

		destRect.x -= (4 * scaleUp/4);
		break;
	default: break;
	}
	lastMovement = moveDir;
	playerMoved = true;
}

int Player::loadMedia(std::string path)
{
	gTexture = textureManager->loadAssetTexture(path);
	SDL_SetTextureColorMod(gTexture, 0xFF / 2, 0xFF, 0xFF);
	if (gTexture == NULL) {
		printf("Failed to load Player texture image!\n");
		return -1;
	}
	return 0;
}
