#ifndef _CAMERA_H
#define _CAMERA_H

#include "Vector2d.h"

class CameraRect
{

public:
	CameraRect(int x, int y, int w, int h) {
		x_ = x;
		y_ = y;
		w_ = w;
		h_ = h;
	}

private:
	int x_;
	int y_;
	int w_;
	int h_;

};

class Camera
{
private:
	// Absolute position of camera (number of
	// pixels from origin of level map)
	Vector2d position_;

	// Target position camera is moving towards
	Vector2d target_;

	// Size of camera
	Vector2d size_;

	// Speed of camera, a value between 0.0 and 1.0
	float speed_;

public:
	Camera(int w, int h, float speed);
	~Camera();

	// Moves camera immediately to coordinates
	void move(int x, int y);
	void moveCenter(int x, int y);

	// Sets camera target
	void goTo(int x, int y);
	void goToCenter(int x, int y);

	// Updates camera position
	void update();

	Vector2d getPosition() { return Vector2d(position_.getX(), position_.getY()); }
	
};

#endif
