#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../gameobject.h"
#include "../component/component.h"
#include <string>
#include <vector>

class GameState
{
public:
    
    virtual void update() = 0;
    
    virtual bool onEnter() = 0;

    virtual bool onExit() {
		gameObjects_.clear();
		return true;
	}
    
    virtual void resume() {}
    
    virtual std::string getStateId() const = 0;
    
	virtual void add(GameObject* o) {
		gameObjects_.push_back(o);
	}

protected:
    
    GameState() : loadingComplete_(false), exiting_(false)
    {
    }
    
    bool loadingComplete_;
    bool exiting_;
    
    std::vector<std::string> textureIdList_;
	std::vector<GameObject*> gameObjects_;
};

#endif