#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <vector>

#include <SDL/SDL.h>
#include "Vector2d.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    
    static InputHandler* getInstance()
    {
        if(instance_ == 0)
        {
            instance_ = new InputHandler();
        }
        
        return instance_;
    }
    
    // init joysticks
    void initialiseJoysticks();
    bool joysticksInitialised() const { return joysticksInitialised_; }
    
    void reset();
    
    // update and clean the input handler
    void update();
    void clean();
    
    // keyboard events
    bool isKeyDown(SDL_Scancode key) const;
    
    // joystick events
    int getAxisX(int joy, int stick) const;
    int getAxisY(int joy, int stick) const;
    bool getButtonState(int joy, int buttonNumber) const;
	bool getTriggerState(int joy, int trigger) const;
    
    // mouse events
    bool getMouseButtonState(int buttonNumber) const;
    Vector2d* getMousePosition() const;
    Vector2d* getPrevMousePosition() const;
    
private:
    
    InputHandler();
    ~InputHandler();
    
    InputHandler(const InputHandler&);
	InputHandler& operator=(const InputHandler&);
    
    // private functions to handle different event types
    
    // handle keyboard events
    void onKeyDown();
    void onKeyUp();
    
    // handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);
    
    // handle joysticks events
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);
    static const int triggerDeadZone_ = 15000;

    // member variables
    
    // keyboard specific
    const Uint8* keystates_;
    
    // joystick specific
    std::vector<std::pair<Vector2d*, Vector2d*>> joystickValues_;
    std::vector<SDL_Joystick*> joysticks_;
    std::vector<std::vector<bool>> buttonStates_;
    std::vector<std::vector<bool>> triggerStates_;
    bool joysticksInitialised_;
    static const int joystickDeadZone_ = 10000;
    
    // mouse specific
    std::vector<bool> mouseButtonStates_;
    Vector2d* mousePosition_;
	Vector2d* prevMousePosition_;
    
    // singleton
    static InputHandler* instance_;
};
typedef InputHandler TheInputHandler;


#endif /* defined(__SDL_Game_Programming_Book__InputHandler__) */