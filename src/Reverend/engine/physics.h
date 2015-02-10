#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

class GameRect;
class GameObject;

class Physics {

public:
	static bool checkCollision(GameObject &a, GameObject &b);
	static bool checkCollision(GameRect &a, GameRect &b);
};

#endif