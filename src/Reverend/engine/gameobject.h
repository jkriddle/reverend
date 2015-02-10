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
	
	GameObject() : position_(0.0f, 0.0f), velocity_(0.0f, 0.0f), acceleration_(0.0f, 0.0f), forward_(0.0f, 0.0f)
	{
	}

	GameObject(const LoaderParams* params) : position_((float)params->getX(), (float)params->getY()), 
		velocity_(0.0f, 0.0f), acceleration_(0.0f, 0.0f), forward_(0.0f, 0.0f) {
		init(params);
	}

	void init(const LoaderParams* params);

	virtual ~GameObject() {}

	int getX()
	{
		return (int)position_.getX();
	}

	int getY()
	{
		return (int)position_.getY();
	}

	virtual int getHeight() { return height_; }
	virtual int getWidth() { return width_; }
	virtual Vector2d getVelocity() { return velocity_;	}
	virtual void setVelocity(Vector2d velocity) { velocity_ = velocity;	}
	virtual void setAcceleration(Vector2d acceleration) { acceleration_ = acceleration;	}
	virtual Vector2d getAcceleration() { return acceleration_;	}
	Vector2d getPosition(){ return position_; }
	void setPosition(Vector2d position){ position_ = position; }
	GameRect getBounds() { 
		return GameRect((int)position_.getX(), (int)position_.getY(), width_, height_);
	}
	
	void addComponent(Component* component) {
		components_.push_back(component);
	}

	std::vector<Component*> getComponents() {
		return components_;
	}
	
	// Retrieve the first component of a specific type
	template <typename T>
	T* getComponent() {
		for(Component* c : components_) {
			T* cType = dynamic_cast<T*>(c);
			if (cType != nullptr) return cType;
		}
		return nullptr;
	}
	
	template <typename T>
	std::vector<T*> getComponents() {
		std::vector<T*> matching;
		for(Component* c : components_) {
			T* cType = dynamic_cast<T*>(c);
			if (cType != nullptr) {
				matching.push_back(cType);
			}
		}
		return matching;
	}

	void sendMessage(Message* message)
	{
		for(Component* c : components_)
		{
			c->receiveMessage(message);
		}	
	}

protected:

	Vector2d position_;
	Vector2d velocity_;
	Vector2d acceleration_;
	Vector2d forward_;

	int width_;
	int height_;
	
	std::vector<Component*> components_;
};

#endif
