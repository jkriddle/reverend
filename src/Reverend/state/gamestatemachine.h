#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include <vector>
#include "gamestate.h"

class GameStateMachine
{
public:
    
    GameStateMachine() {}
    ~GameStateMachine() {}
    
    void update();
    void pushState(GameState* state);
    void changeState(GameState* state);
    void popState();
    
    void clean();

	std::vector<GameState*>& getGameStates() { return gameStates_; }
    
private:
    std::vector<GameState*> gameStates_;
};

#endif