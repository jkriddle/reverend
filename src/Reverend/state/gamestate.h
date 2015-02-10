#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../sdlgameobject.h"
#include "../component/component.h"
#include <string>
#include <vector>

class GameState
{
public:
    
    virtual void update() = 0;
    
    virtual bool onEnter() = 0;

    virtual bool onExit() {
		for(unsigned int i = 0; i < gameObjects_.size(); i++) {
			gameObjects_[i]->clean();
		}
		gameObjects_.clear();
		return true;
	}
    
    virtual void resume() {}
    
    virtual std::string getStateId() const = 0;
    
	virtual void add(SDLGameObject* o) {
		gameObjects_.push_back(o);
	}

protected:
    
    GameState() : loadingComplete_(false), exiting_(false)
    {
    }
    
    bool loadingComplete_;
    bool exiting_;
    
    std::vector<std::string> textureIdList_;
	std::vector<SDLGameObject*> gameObjects_;
};

#endif