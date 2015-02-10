#pragma warning(disable: 4244) // conversion of Vector2d float to int

#include "player.h"
#include "../game.h"
#include "../soundmanager.h"
#include "../component/boxcollider.h"
#include "../component/animatedsprite.h"

Player::Player() : GameObject() {
}

void Player::init(const LoaderParams* pParams)
{
	GameObject::init(pParams);

	addComponent(new BoxCollider(*this));
	addComponent(new RenderingComponent(*this));
}