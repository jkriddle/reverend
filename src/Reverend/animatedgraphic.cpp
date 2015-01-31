#include "animatedgraphic.h"

using namespace std;

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, 
	int animSpeed, int frameCount) : SDLGameObject(pParams), 
	animSpeed_(animSpeed), frameCount_(frameCount)
{
}

void AnimatedGraphic::draw()
{
    SDLGameObject::draw();
}

void AnimatedGraphic::update()
{
    currentTextureFrame_ = int(((SDL_GetTicks() / (1000 / animSpeed_)) % frameCount_));
}

void AnimatedGraphic::clean()
{
    SDLGameObject::clean();
}