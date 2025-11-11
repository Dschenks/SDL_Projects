#pragma once
/**
* @brief Game Object Class handles a game object's position, screen rectangle space, and asset.
*
* @details A parent class creates an instance of this class which will initialize the game space
* rectangle, dimensions and position, and asset texture that will be scaled to the class rectangle.
* Lastly, this will handle basic game update components related to position and assets like moving.
* In order to define the behavior of movement, the parent class will need to link a callback function
* for this function to point to in order to properly update object positions.
* Another function that will require a callback function is frame rendering which will utilize a
* renderer from the main game loop and render appropriately to it.
*/
#include <SDL.h>

class GameObject
{
public:
	GameObject();
	GameObject(int x, int y, int w, int h);
	~GameObject();

	void setX(int x);
	void setY(int y);

	void setW(int w);
	void setH(int h);

	int getX() const;
	int getY() const;
	
	int getW() const;
	int getH() const;

	void move();	// todo: make a callback from a parent component class
	void render();	// todo: make a callback from a parent component class

protected:
private:
	static const int DEFAULT_X = 32;
	static const int DEFAULT_Y = 32;
	static const int DEFAULT_W = 32;
	static const int DEFAULT_H = 32;

	int x, y;
	int w, h;
	SDL_Rect* gRect;
	SDL_Texture* gTexture;
};

