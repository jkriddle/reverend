#pragma warning(disable: 4244) // conversion of Vector2d float to int

#include "inputhandler.h"
#include "game.h"
#include <iostream>

InputHandler* InputHandler::instance_ = 0;

InputHandler::InputHandler() : keystates_(0), joysticksInitialised_(false), mousePosition_(new Vector2d(0,0))
{
    // create button states for the mouse
    for(int i = 0; i < 3; i++)
    {
        mouseButtonStates_.push_back(false);
    }
}

InputHandler::~InputHandler()
{
    // delete anything we created dynamically
    delete keystates_;
    delete mousePosition_;
    
    // clear our arrays
    joystickValues_.clear();
    joysticks_.clear();
    buttonStates_.clear();
    mouseButtonStates_.clear();
}

void InputHandler::clean()
{
    // we need to clean up after ourselves and close the joysticks we opened
    if(joysticksInitialised_)
    {
        for(int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_JoystickClose(joysticks_[i]);
        }
    }
}

void InputHandler::initialiseJoysticks()
{
    // if we haven't already initialised the joystick subystem, we will do it here
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }
    
    // get the number of joysticks, skip init if there aren't any
    if(SDL_NumJoysticks() > 0)
    {
		std::cout << " Found " << SDL_NumJoysticks() << " joysticks";

        for(int i = 0; i < SDL_NumJoysticks(); i++)
        {
            // create a new joystick
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            
            // if the joystick opened correctly we need to populate our arrays
            if(SDL_JoystickOpen(i))
            {
                // push back into the array to be closed later
                joysticks_.push_back(joy);
                
                // create a pair of values for the axes, a vector for each stick
                joystickValues_.push_back(std::make_pair(new Vector2d(0,0),new Vector2d(0,0)));
                
                // create an array to hold the button values
                std::vector<bool> tempButtons;
                
                // fill the array with a false value for each button
                for(int j = 0; j <  SDL_JoystickNumButtons(joy); j++)
                {
                    tempButtons.push_back(false);
                }
                // push the button array into the button state array
                buttonStates_.push_back(tempButtons);
            }
            else
            {
                // if there was an error initialising a joystick we want to know about it
                std::cout << SDL_GetError();
            }
        }
        
        // enable joystick events
        SDL_JoystickEventState(SDL_ENABLE);
        joysticksInitialised_ = true;
        
        std::cout << "Initialised " << joysticks_.size() << " joystick(s)";
    }
    else
    {
        joysticksInitialised_ = false;
    }
}

void InputHandler::reset()
{
    mouseButtonStates_[LEFT] = false;
    mouseButtonStates_[RIGHT] = false;
    mouseButtonStates_[MIDDLE] = false;
}

bool InputHandler::isKeyDown(SDL_Scancode key) const
{
    if(keystates_ != 0)
    {
        if(keystates_[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    return false;
}

int InputHandler::getAxisX(int joy, int stick) const
{
    if(joystickValues_.size() > 0)
    {
        if(stick == 1)
        {
            return joystickValues_[joy].first->getX();
        }
        else if(stick == 2)
        {
            return joystickValues_[joy].second->getX();
        }
    }
    return 0;
}

int InputHandler::getAxisY(int joy, int stick) const
{
    if(joystickValues_.size() > 0)
    {
        if(stick == 1)
        {
            return joystickValues_[joy].first->getY();
        }
        else if(stick == 2)
        {
            return joystickValues_[joy].second->getY();
        }
    }
    return 0;
}

bool InputHandler::getButtonState(int joy, int buttonNumber) const
{
    return buttonStates_[joy][buttonNumber];
}

bool InputHandler::getMouseButtonState(int buttonNumber) const
{
    return mouseButtonStates_[buttonNumber];
}

Vector2d* InputHandler::getMousePosition() const
{
    return mousePosition_;
}

void InputHandler::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                Game::getInstance()->close();
                break;
                
            case SDL_JOYAXISMOTION:
                onJoystickAxisMove(event);
                break;
                
            case SDL_JOYBUTTONDOWN:
                onJoystickButtonDown(event);
                break;
                
            case SDL_JOYBUTTONUP:
                onJoystickButtonUp(event);
                break;
                
            case SDL_MOUSEMOTION:
                onMouseMove(event);
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event);
                break;
                
            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event);
                break;
                
            case SDL_KEYDOWN:
                onKeyDown();
                break;
                
            case SDL_KEYUP:
                onKeyUp();
                break;
                
            default:
                break;
        }
    }
}

void InputHandler::onKeyDown()
{
    keystates_ = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
    keystates_ = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseMove(SDL_Event &event)
{
    mousePosition_->setX(event.motion.x);
    mousePosition_->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event &event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        mouseButtonStates_[LEFT] = true;
    }
    
    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        mouseButtonStates_[MIDDLE] = true;
    }
    
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        mouseButtonStates_[RIGHT] = true;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        mouseButtonStates_[LEFT] = false;
    }
    
    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        mouseButtonStates_[MIDDLE] = false;
    }
    
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        mouseButtonStates_[RIGHT] = false;
    }
}

void InputHandler::onJoystickAxisMove(SDL_Event &event)
{
    int whichOne = event.jaxis.which;
    // left stick move left or right
    if(event.jaxis.axis == 0)
    {
        if (event.jaxis.value > joystickDeadZone_)
        {
            joystickValues_[whichOne].first->setX(1);
        }
        else if(event.jaxis.value < -joystickDeadZone_)
        {
            joystickValues_[whichOne].first->setX(-1);
        }
        else
        {
            joystickValues_[whichOne].first->setX(0);
        }
    }
    
    // left stick move up or down
    if(event.jaxis.axis == 1)
    {
        if (event.jaxis.value > joystickDeadZone_)
        {
            joystickValues_[whichOne].first->setY(1);
        }
        else if(event.jaxis.value < -joystickDeadZone_)
        {
            joystickValues_[whichOne].first->setY(-1);
        }
        else
        {
            joystickValues_[whichOne].first->setY(0);
        }
    }
    
    // right stick move left or right
    if(event.jaxis.axis == 2)
    {
        if (event.jaxis.value > joystickDeadZone_)
        {
            joystickValues_[whichOne].second->setX(1);
        }
        else if(event.jaxis.value < -joystickDeadZone_)
        {
            joystickValues_[whichOne].second->setX(-1);
        }
        else
        {
            joystickValues_[whichOne].second->setX(0);
        }
    }
    
    // right stick move up or down
    if(event.jaxis.axis == 3)
    {
        if (event.jaxis.value > joystickDeadZone_)
        {
            joystickValues_[whichOne].second->setY(1);
        }
        else if(event.jaxis.value < -joystickDeadZone_)
        {
            joystickValues_[whichOne].second->setY(-1);
        }
        else
        {
            joystickValues_[whichOne].second->setY(0);
        }
    }
}

void InputHandler::onJoystickButtonDown(SDL_Event &event)
{
    int whichOne = event.jaxis.which;
    
    buttonStates_[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event &event)
{
    int whichOne = event.jaxis.which;
    
    buttonStates_[whichOne][event.jbutton.button] = false;
}