#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL/SDL.h>
#include <string>
#include <vector>
#include "vector2d.h"
#include "gamerect.h"
#include "texturemanager.h"
#include "loaderparams.h"
#include "component/component.h"

class Message;

class GameObject {

public:
	
	GameObject() : position(0.0f, 0.0f), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), forward(0.0f, 0.0f)
	{
	}

	GameObject(const LoaderParams* params) : position((float)params->x, (float)params->y), 
		velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), forward(0.0f, 0.0f) {
		init(params);
	}

	void init(const LoaderParams* params);

	virtual ~GameObject() {}

	GameRect getBounds() { 
		return GameRect((int)position.x, (int)position.y, width, height);
	}
	
	void addComponent(Component* component) {
		components.push_back(component);
	}

	std::vector<Component*> getComponents() {
		return components;
	}

	// Use for in-game initialization
	virtual void start();

	void update();
	
	// Retrieve the first component of a specific type
	template <typename T>
	T* getComponent() {
		for(Component* c : components) {
			T* cType = dynamic_cast<T*>(c);
			if (cType != nullptr) return cType;
		}
		return nullptr;
	}
	
	template <typename T>
	std::vector<T*> getComponents() {
		std::vector<T*> matching;
		for(Component* c : components) {
			T* cType = dynamic_cast<T*>(c);
			if (cType != nullptr) {
				matching.push_back(cType);
			}
		}
		return matching;
	}

	void sendMessage(Message* message)
	{
		for(Component* c : components)
		{
			c->receiveMessage(message);
		}	
	}
	
	Vector2d position;
	Vector2d velocity;
	Vector2d acceleration;
	Vector2d forward;

	int width;
	int height;
	std::vector<Component*> components;

protected:
	bool started_;
	
};

#endif
