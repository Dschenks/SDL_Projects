#include "GameErrors.h"


void GameErrors::SDL_IMG_PrintError(std::string fmt ...)
{
	fmt.append(_SDL_FormatErrorMsg(" SDL_image Error: %s\n", IMG_GetError()));
	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt.c_str(), args);
	va_end(args);
}

void GameErrors::SDL_PrintError(std::string fmt ...)
{
	fmt.append(_SDL_FormatErrorMsg(" SDL Error: %s\n", SDL_GetError()));
	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt.c_str(), args);
	va_end(args);
}

std::string GameErrors::_SDL_FormatErrorMsg(std::string errorMsgFmt, std::string errorMsg)
{
	if (errorMsg == "") return "\n";	// If the return string is nothing, don't return a message

	// Create temp C char string to format with the SDL Error Message
	size_t tempStrSize = errorMsg.size() + errorMsgFmt.size();
	char* tempStr = new char[tempStrSize];

	int c = snprintf(tempStr, tempStrSize, errorMsgFmt.c_str(), errorMsg.c_str());

	errorMsg = tempStr;		// swap temp with returned string
	delete[] tempStr;		// cleanup temp string

	return errorMsg;
}