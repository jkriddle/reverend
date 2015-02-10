#pragma warning(disable: 4244) // conversion of Vector2d float to int

#include "player.h"
#include "../engine/game.h"
#include "../engine/soundmanager.h"
#include "../engine/component/boxcollider.h"
#include "../engine/component/animatedsprite.h"

Player::Player() : GameObject() {
}

void Player::init(const LoaderParams* pParams)
{
	GameObject::init(pParams);

	addComponent(new BoxCollider(*this));
	addComponent(new RenderingComponent(*this));
}