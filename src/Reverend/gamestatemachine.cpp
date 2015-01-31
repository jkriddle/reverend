#include "gamestatemachine.h"
#include <iostream>

void GameStateMachine::clean()
{
    if(!gameStates_.empty())
    {
        gameStates_.back()->onExit();

        delete gameStates_.back();
        
        gameStates_.clear();
    }
}

void GameStateMachine::update()
{
    if(!gameStates_.empty())
    {
        gameStates_.back()->update();
	}
}

void GameStateMachine::draw()
{
    if(!gameStates_.empty())
    {
        gameStates_.back()->draw();
    }
}

void GameStateMachine::pushState(GameState *state)
{
    gameStates_.push_back(state);
    gameStates_.back()->onEnter();
}

void GameStateMachine::popState()
{
    if(!gameStates_.empty())
    {
        gameStates_.back()->onExit();
        gameStates_.pop_back();
    }
    
    gameStates_.back()->resume();
}

void GameStateMachine::changeState(GameState *state)
{
    if(!gameStates_.empty())
    {
        if(gameStates_.back()->getStateId() == state->getStateId())
        {
            return; // do nothing
        }

		gameStates_.back()->onExit();
		gameStates_.pop_back();
    }

	// initialise it
    state->onEnter();
    
    // push back our new state
    gameStates_.push_back(state);
}