#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL/SDL.h>
#include <string>
#include <vector>
#include "texturemanager.h"
#include "loaderparams.h"

class Message;

class GameObject {
public:
	virtual void update() = 0;
	virtual void clean() = 0;
protected:
	GameObject() {}
	GameObject(const LoaderParams* params) {}
	virtual ~GameObject() {}
};

#endif