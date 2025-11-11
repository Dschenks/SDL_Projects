#pragma once
#include "GameTypes.h"
#include <SDL.h>
#include "Callback.h"
#include "WindowScreen.h"
#include "TextureManager.h"

class GameObjectCallbacks
{
public:
	GameObjectCallbacks();
	// makes a callback from a parent component class e.g. goomba class has an object and tick will be called from GameObject and handled in Goomba class
	void init(WindowScreen* windowScreen, TextureManager* textureManager)
	{
		if ((initCallback != NULL) && (initCallback->isValid())) {
			this->initCallback->execute(windowScreen, textureManager);
		}
	}
	void close()
	{
		if ((closeCallback != NULL) && (closeCallback->isValid())) {
			this->closeCallback->execute();
		}
	}
	void tick()
	{
		if ((tickCallback != NULL) && (tickCallback->isValid())) {
			this->tickCallback->execute();
		}
	}
	void render()
	{
		if ((renderCallback != NULL) && (renderCallback->isValid())) {
			this->renderCallback->execute();
		}
	}
	void move(GameTypes::move_dir_t moveDir)
	{
		if ((moveCallback != NULL) && (moveCallback->isValid())) {
			this->moveCallback->execute(moveDir);
		}
	}

	void setInitCallback(GenericCallback<WindowScreen*, TextureManager*>& callback)
	{
		initCallback = &callback;
	}
	void setCloseCallback(GenericCallback<>& callback)
	{
		closeCallback = &callback;
	}
	void setTickCallback(GenericCallback<>& callback)
	{
		tickCallback = &callback;
	}
	void setRenderCallback(GenericCallback<>& callback)
	{
		renderCallback = &callback;
	}
	void setMoveCallback(GenericCallback<GameTypes::move_dir_t>& callback)
	{
		moveCallback = &callback;
	}

private:
	GenericCallback<WindowScreen*, TextureManager*>* initCallback;
	GenericCallback<>* closeCallback;
	GenericCallback<>* tickCallback;
	GenericCallback<GameTypes::move_dir_t>* moveCallback;
	GenericCallback<>* renderCallback;
};
