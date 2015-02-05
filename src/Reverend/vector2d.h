#ifndef VECTOR2D_H
#define VECTOR2D_H

#include<math.h>

class Vector2d {

public:
	static const Vector2d* ZERO;
	static const Vector2d* NORTH;
	static const Vector2d* NORTH_EAST;
	static const Vector2d* EAST;
	static const Vector2d* SOUTH_EAST;
	static const Vector2d* SOUTH;
	static const Vector2d* SOUTH_WEST;
	static const Vector2d* WEST;
	static const Vector2d* NORTH_WEST;
	
	Vector2d() : x_(0), y_(0) {}
	Vector2d(float x, float y): x_(x), y_(y) {}
	float getX() { return x_; }
	float getY() { return y_; }
	void set(float x, float y) { x_ = x; y_ = y; }
	void setX(float x) { x_ = x; }
	void setY(float y) { y_ = y; }
	float length() { return sqrt(x_ * x_ + y_ * y_); }

	Vector2d operator+(const Vector2d& v2) const {
		return Vector2d(x_ + v2.x_, y_ + v2.y_);
	}

	friend Vector2d& operator+=(Vector2d& v1, const Vector2d& v2) {

		v1.x_ += v2.x_;
		v1.y_ += v2.y_;
		return v1;
	}

	Vector2d operator*(float scalar) {
		return Vector2d(x_ * scalar, y_ * scalar);
	}

	Vector2d& operator*=(float scalar) {
		x_ *= scalar;
		y_ *= scalar;
		return *this;
	}

	Vector2d operator-(const Vector2d& v2) const {
		return Vector2d(x_ - v2.x_, y_ - v2.y_);
	}

	friend Vector2d& operator-=(Vector2d& v1, const Vector2d& v2) {
		v1.x_ -= v2.x_;
		v1.y_ -= v2.y_;
		return v1;
	}
	
	friend bool operator==(Vector2d& v1, const Vector2d& v2) {
		return (v1.x_ == v2.x_ && v1.y_ == v2.y_);
	}
	
	friend bool operator!=(Vector2d& v1, const Vector2d& v2) {
		return !(v1.x_ == v2.x_ && v1.y_ == v2.y_);
	}

	Vector2d operator/(float scalar) {
		return Vector2d(x_ / scalar, y_ / scalar);
	}

	Vector2d& operator/=(float scalar) {
		x_ /= scalar;
		y_ /= scalar;
		return *this;
	}

	void normalize() {
		float l = length();
		if ( l > 0) { // we never want to attempt to divide by 0
			(*this) *= 1 / l;
		}
	}

private:
	float x_;
	float y_;

};

#endif