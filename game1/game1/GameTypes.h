#pragma once

#include <SDL.h>
#include "gameTime.h"
#include <string>
#include <math.h>

namespace GameTypes {
	typedef enum {
		MOVE_DIR_NONE = 0,
		MOVE_DIR_UP,
		MOVE_DIR_RIGHT,
		MOVE_DIR_DOWN,
		MOVE_DIR_LEFT
	} move_dir_t;

	typedef uint16_t fpp;	// frames/pixel
	typedef uint8_t ftps;	// ft/s

	static const uint8_t DEFAULT_PLAYER_SPEED = 5; // 5ft/s. frame/px = 1.875frame/1px

	static constexpr int pxPerTile = 16;		// px/tile
	static constexpr double ftPerTile = 5.0;	// ft/tile (width/height of player)
	static constexpr double ftPerPx = (ftPerTile / pxPerTile);	// ft/pixel
	static constexpr double pxPerFt = (pxPerTile / ftPerTile);	// pixel/ft

	static_assert(GameTypes::ftPerPx != 0, "Div-0 Error: Feet-per-pixel scalar is equal to 0!");

	constexpr fpp speed2FramePerPx(uint8_t speed, GameTime::fps fps) noexcept;
	GameTime::fps speed2pps(uint8_t speed);

	typedef struct {
		ftps ftps;
		GameTime::fps pps;
	} movementSpeed_t;
}


namespace SpriteTypes {
	static const std::string flagStrings[] = {
		"Standing",
		"Running Left",
		"Running Right",
		"Runnning Up",
		"Running Down"
	};

	typedef enum {
		SPRITE_STANDING = 1 << 0,
		SPRITE_RUNNING_LEFT = 1 << 1,
		SPRITE_RUNNING_RIGHT = 1 << 2,
		SPRITE_RUNNING_UP = 1 << 3,
		SPRITE_RUNNING_DOWN = 1 << 4,
	} spriteAssetFlags_t;

	const uint32_t SPRITE_ASSET_ALL_FLAGS = 0x1F;

	constexpr uint32_t getRSB(uint32_t flag) { return flag & (~flag + 1); }

	constexpr bool checkFlagSupported(uint32_t supportedFlags, uint32_t flag) { return !!(getRSB(flag) & supportedFlags); }

	inline uint8_t flag2index(uint32_t flag) {
		flag = flag & (~flag + 1);
		return (uint8_t)log2(flag);
	}

	constexpr uint8_t flag2index(uint32_t supportedFlags, uint32_t flag) {
		flag = getRSB(flag);
		uint8_t index = 0;
		for (uint32_t i = 0; i < 32; i++) {
			if ((1 << i) & supportedFlags) {
				if (flag & (1 << i)) return index;
				else index++;
			}
		}
		return index;	// should not get here, there was a problem.  please check flag is supported
	}

	typedef struct {
		union {
			struct {
				uint16_t gTextureSet : 1;
				uint16_t srcRectSet : 1;
				uint16_t rotationSet : 1;
				uint16_t flipSet : 1;
				uint16_t alphaSet : 1;
				uint16_t scaleSet : 1;
			};
			uint16_t paramSet;
		};
		SDL_Texture* gTexture;
		SDL_Rect srcRect;
		double rotation;
		SDL_RendererFlip flip;
		uint8_t alpha;
		uint8_t scale;
	} spriteAssetModifiers_t;
}