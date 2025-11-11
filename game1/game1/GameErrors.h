#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cstdarg>

class GameErrors
{
public:
	static void SDL_IMG_PrintError(std::string fmt...);
	static void SDL_PrintError(std::string fmt...);
private:
	static std::string _SDL_FormatErrorMsg(std::string errorMsgFmt, std::string errorMsg);
};

