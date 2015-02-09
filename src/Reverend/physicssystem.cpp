#include "physicssystem.h"
#include "object/sdlgameobject.h"

bool PhysicsSystem::checkCollision(SDLGameObject &a, SDLGameObject &b) {
	if (&a == &b) return false;
	int aX = a.getX();
	int aY = a.getY();
	int aW = a.getWidth();
	int aH = a.getHeight();

	int bX = b.getX();
	int bY = b.getY();
	int bW = b.getWidth();
	int bH = b.getHeight();

	if (aX < bX + bW &&
		aX + aW > bX &&
		aY < bY + bH &&
		aH + aY > bY) {
		// collision
			return true;
	}
	return false;
}

bool PhysicsSystem::checkCollision(GameRect &a, GameRect &b) {
	if (&a == &b) return false;
	int aX = a.getX();
	int aY = a.getY();
	int aW = a.getWidth();
	int aH = a.getHeight();

	int bX = b.getX();
	int bY = b.getY();
	int bW = b.getWidth();
	int bH = b.getHeight();

	if (aX < bX + bW &&
		aX + aW > bX &&
		aY < bY + bH &&
		aH + aY > bY) {
		// collision
			return true;
	}
	return false;
}