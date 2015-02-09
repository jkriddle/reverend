#pragma once

#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include <SDL/SDL.h>
#include "gameobject.h"
#include "../vector2d.h"
#include "../inputhandler.h"

class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual int getX();
	virtual int getY();
	virtual int getHeight() { return height_; }
	virtual int getWidth() { return width_; }
	virtual Vector2d getVelocity() { return velocity_;	}
	virtual void setVelocity(Vector2d velocity) { velocity_ = velocity;	}
	virtual void setAcceleration(Vector2d acceleration) { acceleration_ = acceleration;	}
	virtual Vector2d getAcceleration() { return acceleration_;	}
	Vector2d SDLGameObject::getPosition(){ return position_; }
	void setPosition(Vector2d position){ position_ = position; }
	const std::string& getTextureId() { return textureId_; }
	
	void addComponent(Component* component) {
		components_.push_back(component);
	}

	std::vector<Component*> getComponents() {
		return components_;
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

	int currentTextureRow_;
	int currentTextureFrame_;

	std::string textureId_;
};

#endif