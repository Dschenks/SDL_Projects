#include "gameTime.h"

using ms = std::chrono::milliseconds;

GameTime::GameTime()
{
	gameStartTick = std::chrono::high_resolution_clock::time_point();
	lastFrameTick = ms();

	frameRate = DEFAULT_FPS;
	frameMs = fps2ms(frameRate);

	avgFps = (double)frameRate;
	frameCnt = 0;
}

void GameTime::init()
{
	gameStartTick = std::chrono::high_resolution_clock::now();
	lastFrameTick = std::chrono::duration_cast<ms>(gameStartTick - gameStartTick);
}

void GameTime::resetClock()
{
	// Reset Frame Statistics
	avgFps = (double)frameRate;
	frameCnt = 0;

	// re-intialize time counters
	init();
}

void GameTime::setFrameRate(fps fps)
{
	if (fps > 200) return;

	frameRate = fps;
	frameMs = fps2ms(fps);

	resetClock();
}

void GameTime::setFrameRate(double fps)
{
	if (fps > 200) return;

	frameRate = fps;
	frameMs = fps2ms(fps);

	resetClock();
}

std::chrono::milliseconds GameTime::getCurrentTick() const
{
	return std::chrono::duration_cast<ms>(std::chrono::high_resolution_clock::now() - gameStartTick);
	// return std::chrono::milliseconds();
}

bool GameTime::checkNewFrameTick() const
{
	ms currentTick = getCurrentTick();
	if ((currentTick - lastFrameTick) > frameMs) return true;
}

bool GameTime::checkNewFrameTick(ms lastFrameTick, fps fps, GameTime* gameClock)
{
	ms currentTick = gameClock->getCurrentTick();
	if ((currentTick - lastFrameTick) > fps2ms(fps)) return true;
}

void GameTime::updateFrameTime()
{
	ms currentTick = getCurrentTick();
	ms frameTime =  currentTick - lastFrameTick;
	lastFrameTick = currentTick;
	
	fps currentFrameFps = ms2fps(frameTime);
	
	if (frameCnt > 0) {
		avgFps = (avgFps / frameCnt) * (frameCnt / ((double)frameCnt + 1)) + (currentFrameFps / ((double)frameCnt + 1));
	}
	frameCnt++;
}

std::chrono::milliseconds GameTime::fps2ms(fps fps)
{
	return ms((1000 / fps));
}

std::chrono::milliseconds GameTime::fps2ms(double fps)
{
	return ms((int)(1000.0 / fps));
}

GameTime::fps GameTime::ms2fps(std::chrono::milliseconds ms)
{
	return ((1.0 / ms.count()) * 1000.0);
}
