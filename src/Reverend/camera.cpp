#include "camera.h"
#include <math.h>

Camera::Camera(int w, int h, float speed)
{
	size_.setX(w);
	size_.setY(h);

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
	position_.setX(x);
	position_.setY(y);
	target_.setX(x);
	target_.setY(y);
}

//Centers camera at coordinates
void Camera::moveCenter(int x, int y)
{
	x = x - (size_.getX() / 2);
	y = y - (size_.getY() / 2);

	position_.setX(x);
	position_.setY(y);
	target_.setX(x);
	target_.setY(y);
}

//Sets target_ to coordinates
void Camera::goTo(int x, int y)
{
	target_.setX(x);
	target_.setY(y);
}

//Centers target_ at coordinates
void Camera::goToCenter(int x, int y)
{
	x = x - (size_.getX() / 2);
	y = y - (size_.getY() / 2);

	target_.setX(x);
	target_.setY(y);
}

//This function allows us to do a cool camera
//scrolling effect by moving towards a target_
//position_ over time.
void Camera::update()
{
	//X distance to target_, Y distance to target_, and Euclidean distance
	float x, y, d;

	//Velocity magnitudes
	float vx, vy, v;

	//Find x and y
	x = (float)(target_.getX() - position_.getX());
	y = (float)(target_.getY() - position_.getY());
	
	// No animation for now
	position_.setX(target_.getX());
	position_.setY(target_.getY());
	return;

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

CameraRect Camera::getTileBounds(int tilesize_)
{
	int x = (int)(position_.getX() / tilesize_);
	int y = (int)(position_.getY() / tilesize_);

	//+1 in case camera size_ isn't divisible by tilesize_
	//And +1 again because these values start at 0, and
	//we want them to start at one
	int w = (int)(size_.getX() / tilesize_ + 2);
	int h = (int)(size_.getY() / tilesize_ + 2);

	//And +1 again if we're offset from the tile
	if(x % tilesize_ != 0)
		w++;
	if(y % tilesize_ != 0)
		h++;

	return CameraRect(x, y, w, h);
}
