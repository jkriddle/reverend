#ifndef Input_H
#define Input_H

#include <iostream>
#include <vector>

#include <SDL/SDL.h>
#include "Vector2d.h"

enum MouseButtons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class Input
{
public:
    
    static Input& getInstance()
    {
		static Input instance_;
        return instance_;
    }
    
    // init joysticks
    void initialiseJoysticks();
    bool joysticksInitialised() const { return joysticksInitialised_; }
    
    void reset();
    
    // update and clean the input handler
    void update();
    void clean();
    bool cdown;

    // keyboard events
    bool isKeyDown(SDL_Scancode key) const;
	bool isKeyPressed(SDL_Scancode key) const;
    
    // joystick events
    int getAxisX(int joy, int stick) const;
    int getAxisY(int joy, int stick) const;
    bool getButtonState(int joy, int buttonNumber) const;
	bool getTriggerState(int joy, int trigger) const;
    
    // mouse events
    bool getMouseButtonState(int buttonNumber) const;
	bool getMouseButtonPress(int buttonNumber) const;
    Vector2d getMousePosition() const;
    Vector2d getPrevMousePosition() const;
    
	bool isQuitting() { return quitting_; }

    void onQuit();
    ~Input();

private:
    
    Input();
    
    // private functions to handle different event types
    
    // handle keyboard events
    void onKeyDown();
    void onKeyUp();
	void compareKeystates();
    
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
	Uint8* prevKeystates_;
    
    // joystick specific
    std::vector<std::pair<Vector2d*, Vector2d*>> joystickValues_;
    std::vector<SDL_Joystick*> joysticks_;
    std::vector<std::vector<bool>> buttonStates_;
    std::vector<std::vector<bool>> triggerStates_;
    bool joysticksInitialised_;
    static const int joystickDeadZone_ = 10000;
    
    // mouse specific
    std::vector<bool> mouseButtonStates_;
	Uint8* prevMouseButtonStates_;
    Vector2d mousePosition_;
	Vector2d prevMousePosition_;
	bool quitting_;
    
};
typedef Input Input;


#endif 