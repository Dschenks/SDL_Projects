#include "gameObject.h"

GameObject::GameObject() :
	x(DEFAULT_X), y(DEFAULT_Y), w(DEFAULT_W), h(DEFAULT_H), gTexture(NULL)
{
	gRect = new SDL_Rect { x, y, w, h };
	callbacks = new GameObjectCallbacks();
}

GameObject::GameObject(int x, int y, int w, int h) : 
	x(x), y(y), w(w), h(h), gTexture(NULL)
{
	gRect = new SDL_Rect{ x, y, w, h };
}

GameObject::~GameObject()
{
	//delete gRect;
	//delete gTexture;
}

void GameObject::setX(int x)
{
	this->x = x;
}

void GameObject::setY(int y)
{
	this->y = y;
}

void GameObject::setW(int w)
{
	this->w = w;
}

void GameObject::setH(int h)
{
	this->h = h;
}

int GameObject::getX() const
{
	return x;
}

int GameObject::getY() const
{
	return y;
}

int GameObject::getW() const
{
	return w;
}

int GameObject::getH() const
{
	return h;
}
