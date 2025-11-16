#pragma once
#include <chrono>

class GameTime
{
public:
	typedef uint16_t fps;
	typedef std::chrono::milliseconds ms;

	GameTime();

	void init();

	void resetClock();

	void setFrameRate(fps fps);
	void setFrameRate(double fps);
	fps getFrameRate() const { return frameRate; }
	size_t getFrameCount() const { return frameCnt; }
	
	bool checkNewFrameTick() const;
	static bool checkNewFrameTick(ms lastFrameTick, fps fps, GameTime* gameClock);
	void updateFrameTime();

	std::chrono::milliseconds getCurrentTick() const;
	
	static std::chrono::milliseconds fps2ms(fps fps);
	static std::chrono::milliseconds fps2ms(double fps);
	static fps ms2fps(std::chrono::milliseconds ms);

	static const fps DEFAULT_FPS = 30;

private:
	std::chrono::high_resolution_clock::time_point gameStartTick;
	std::chrono::milliseconds lastFrameTick;


	fps frameRate;
	std::chrono::milliseconds frameMs;

	double avgFps;
	size_t frameCnt;
};

