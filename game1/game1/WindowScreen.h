#pragma once
class WindowScreen
{
public:
	static int getScreenWidth() { return screenWidth; }
	static int getScreenHeight() { return screenHeight; }
	static void setScreenWidth(int newScreenWidth) { screenWidth = newScreenWidth; }
	static void setScreenHeight(int newScreenHeight) { screenHeight = newScreenHeight; }

	WindowScreen();
private:
	static int screenWidth;
	static int screenHeight;
};
