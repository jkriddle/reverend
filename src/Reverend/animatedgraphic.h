#pragma once
#ifndef ANIMATEDGRAPHIC_H
#define ANIMATEDGRAPHIC_H

#include <iostream>
#include "objects/sdlgameobject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
  
    AnimatedGraphic(const LoaderParams* pParams, int animSpeed, int frameCount);
   
    virtual void draw();
    virtual void update();
    virtual void clean();
    
private:
    
    int animSpeed_;
    int frameCount_;
};

#endif
