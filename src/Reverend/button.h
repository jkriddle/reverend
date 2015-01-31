#ifndef BUTTON_H
#define BUTTON_H

#include <SDL\SDL.h>
#include "sdlgameobject.h"
#include "loaderparams.h"
#include "vector2d.h"

enum ButtonState {
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};

class Button : public SDLGameObject
{
public:
	Button(const LoaderParams* pParams, void (*callback)());
	virtual void draw();
	virtual void update();
	virtual void clean();
	void (*callback_)();
	bool released_;
};

#endif