#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL/SDL.h>
#include <string>
#include <vector>
#include "../texturemanager.h"
#include "../loaderparams.h"
#include "../component/component.h"

class Message;

class GameObject {
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
protected:
	GameObject(const LoaderParams* params) {}
	virtual ~GameObject() {}
	std::vector<Component*> components_;
};

#endif