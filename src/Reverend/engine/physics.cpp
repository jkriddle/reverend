#include "physics.h"
#include "gameobject.h"

bool Physics::checkCollision(GameObject &a, GameObject &b) {
	if (&a == &b) return false;
	int aX = a.position.x;
	int aY = a.position.y;
	int aW = a.width;
	int aH = a.height;

	int bX = b.position.x;
	int bY = b.position.y;
	int bW = b.width;
	int bH = b.height;

	if (aX < bX + bW &&
		aX + aW > bX &&
		aY < bY + bH &&
		aH + aY > bY) {
		// collision
			return true;
	}
	return false;
}

bool Physics::checkCollision(GameRect &a, GameRect &b) {
	if (&a == &b) return false;
	int aX = a.x;
	int aY = a.y;
	int aW = a.width;
	int aH = a.height;

	int bX = b.x;
	int bY = b.y;
	int bW = b.width;
	int bH = b.height;

	if (aX < bX + bW &&
		aX + aW > bX &&
		aY < bY + bH &&
		aH + aY > bY) {
		// collision
			return true;
	}
	return false;
}