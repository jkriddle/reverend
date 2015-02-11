#include "physics.h"
#include "gameobject.h"

bool Physics::checkCollision(GameObject &a, GameObject &b) {
	if (&a == &b) return false;
	int aX = (int)a.position.x;
	int aY = (int)a.position.y;
	int aW = a.width;
	int aH = a.height;

	int bX = (int)b.position.x;
	int bY = (int)b.position.y;
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
	int aX = (int)a.x;
	int aY = (int)a.y;
	int aW = a.width;
	int aH = a.height;

	int bX = (int)b.x;
	int bY = (int)b.y;
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