#include "physicssystem.h"
#include "object/sdlgameobject.h"

bool PhysicsSystem::checkCollision(SDLGameObject &a, SDLGameObject &b) {
	if (&a == &b) return false;

	if (a.getX() < b.getX() + b.getWidth() &&
		a.getX() + a.getWidth() > b.getX() &&
		a.getY() < b.getY() + b.getHeight() &&
		a.getHeight() + a.getY() > b.getY()) {
		// collision
			return true;
	}
	return false;
}