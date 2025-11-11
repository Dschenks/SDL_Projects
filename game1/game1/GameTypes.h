#pragma once

namespace GameTypes {
	typedef enum {
		MOVE_DIR_NONE = 0,
		MOVE_DIR_UP,
		MOVE_DIR_RIGHT,
		MOVE_DIR_DOWN,
		MOVE_DIR_LEFT
	} move_dir_t;
}


namespace SpriteTypes {
	typedef enum {
		SPRITE_STANDING_1 = 1 << 1,
		SPRITE_STANDING_2 = 1 << 2,
		SPRITE_RUNNING_LEFT_1 = 1 << 3,
		SPRITE_RUNNING_LEFT_2 = 1 << 4,
	} spriteAssetFlags_t;
}