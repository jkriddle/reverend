#pragma once
#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

class SDLGameObject;

class PhysicsSystem {

public:
	static bool checkCollision(SDLGameObject &a, SDLGameObject &b);

};

#endif