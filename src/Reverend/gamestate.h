#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>

class GameState
{
public:
    
    virtual ~GameState() {}
    
    virtual void update() = 0;
    virtual void draw() = 0;
    
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    
    virtual void resume() {}
    
    virtual std::string getStateId() const = 0;
    
protected:
    
    GameState() : loadingComplete_(false), exiting_(false)
    {
        
    }
    
    bool loadingComplete_;
    bool exiting_;
    
    std::vector<std::string> textureIdList_;
};

#endif