#include "camera.h"
#include <math.h>

Camera::Camera(int w, int h, float speed)
{
	size_.setX((float)w);
	size_.setY((float)h);

	if(speed < 0.0)
		speed = 0.0;
	if(speed > 1.0)
		speed = 1.0;

	speed_ = speed;
}

Camera::~Camera()
{
}

//Moves camera to coordinates
void Camera::move(int x, int y)
{
	position_.setX((float)x);
	position_.setY((float)y);
	target_.setX((float)x);
	target_.setY((float)y);
}

//Centers camera at coordinates
void Camera::moveCenter(int x, int y)
{
	x = x - (int)(size_.getX() / 2);
	y = y - (int)(size_.getY() / 2);

	position_.setX((float)x);
	position_.setY((float)y);
	target_.setX((float)x);
	target_.setY((float)y);
}

//Sets target_ to coordinates
void Camera::goTo(int x, int y)
{
	target_.setX((float)x);
	target_.setY((float)y);
}

//Centers target_ at coordinates
void Camera::goToCenter(int x, int y)
{
	x = x - (int)(size_.getX() / 2);
	y = y - (int)(size_.getY() / 2);

	target_.setX((float)x);
	target_.setY((float)y);
}

// This function allows us to do a scrolling effect by moving towards a target_
// position_ over time. NOT CURRENTLY USED.
void Camera::update()
{
	// No animation for now
	position_.setX(target_.getX());
	position_.setY(target_.getY());
	return;

	//X distance to target_, Y distance to target_, and Euclidean distance
	float x, y, d;

	//Velocity magnitudes
	float vx, vy, v;

	//Find x and y
	x = (float)(target_.getX() - position_.getX());
	y = (float)(target_.getY() - position_.getY());

	//If we're within 1 pixel of the target_ already, just snap
	//to target_ and stay there. Otherwise, continue
	if((x*x + y*y) <= 1)
	{
		position_.setX(target_.getX());
		position_.setY(target_.getY());
	}
	else
	{
		//Distance formula
		d = sqrt((x*x + y*y));

		//We set our velocity to move 1/60th of the distance to
		//the target_. 60 is arbitrary, I picked it because I intend
		//to run this function once every 60th of a second. We also
		//allow the user to change the camera speed via the speed member
		v = (d * speed_)/60;

		//Keep v above 1 pixel per update, otherwise it may never get to
		//the target_. v is an absolute value thanks to the squaring of x
		//and y earlier
		if(v < 1.0f)
			v = 1.0f;
		
		//Similar triangles to get vx and vy
		vx = x * (v/d);
		vy = y * (v/d);

		//Then update camera's position_ and we're done
		position_.setX(position_.getX() + vx);
		position_.setY(position_.getY() + vy);
	}
}
