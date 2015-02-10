#pragma once
#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

class GameRect;
class GameObject;

class PhysicsSystem {

public:
	static bool checkCollision(GameObject &a, GameObject &b);
	static bool checkCollision(GameRect &a, GameRect &b);
};

#endif