#include <SDL/SDL.h>
#include <iostream>

class GameObject {
public:
	GameObject(SDL_Texture* texture, int x, int y);
	~GameObject();
	int getX() { return x_; }
	int getY() { return y_; }
	SDL_Texture* getTexture() { return texture_; }
	void setPos(int x, int y);
private:
	int x_;
	int y_;
	SDL_Texture* texture_;
};