#pragma warning(disable: 4244) // conversion of Vector2d float to int

#include "gameobject.h"

void GameObject::init(const LoaderParams* params) {
	width_ = params->getWidth();
	height_ = params->getHeight();
}