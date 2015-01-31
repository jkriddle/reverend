//
//  AnimatedGraphic.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 17/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef ANIMATEDGRAPHIC_H
#define ANIMATEDGRAPHIC_H

#include <iostream>
#include "sdlgameobject.h"

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
