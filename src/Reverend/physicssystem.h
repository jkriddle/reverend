#pragma once
#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

class GameRect;
class SDLGameObject;

class PhysicsSystem {

public:
	static bool checkCollision(SDLGameObject &a, SDLGameObject &b);
	static bool checkCollision(GameRect &a, GameRect &b);
};

#endif