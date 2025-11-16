#include "GameTypes.h"

constexpr GameTypes::fpp GameTypes::speed2FramePerPx(uint8_t speed, GameTime::fps fps) noexcept
{
	/**
	* @notes:
	*	ex: speed = 5ft/s
	*	frames/ft = fps / speed => frames/ft
	*	frames/px = frames/ft * ft/px => frames/px at a given speed!
	*/
	if (speed == 0) return 0;	// catch Div-0

	double framesPerFt = (fps / speed);
	return (GameTypes::fpp) ceil( (double)framesPerFt * GameTypes::ftPerPx);
}

GameTime::fps GameTypes::speed2pps(uint8_t speed)
{
	return (GameTime::fps)ceil((double)speed * GameTypes::pxPerFt);
}
