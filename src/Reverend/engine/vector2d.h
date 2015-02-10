#ifndef VECTOR2D_H
#define VECTOR2D_H

#include<math.h>

class Vector2d {

public:
	static const Vector2d ZERO;
	static const Vector2d NORTH;
	static const Vector2d NORTH_EAST;
	static const Vector2d EAST;
	static const Vector2d SOUTH_EAST;
	static const Vector2d SOUTH;
	static const Vector2d SOUTH_WEST;
	static const Vector2d WEST;
	static const Vector2d NORTH_WEST;
	
	Vector2d() : x(0), y(0) {}
	Vector2d(float x, float y): x(x), y(y) {}
	float length() { return sqrt(x * x + y * y); }

	Vector2d operator+(const Vector2d& v2) const {
		return Vector2d(x + v2.x, y + v2.y);
	}

	friend Vector2d& operator+=(Vector2d& v1, const Vector2d& v2) {

		v1.x += v2.x;
		v1.y += v2.y;
		return v1;
	}

	Vector2d operator*(float scalar) {
		return Vector2d(x * scalar, y * scalar);
	}

	Vector2d& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2d operator-(const Vector2d& v2) const {
		return Vector2d(x - v2.x, y - v2.y);
	}

	friend Vector2d& operator-=(Vector2d& v1, const Vector2d& v2) {
		v1.x -= v2.x;
		v1.y -= v2.y;
		return v1;
	}
	
	friend bool operator==(Vector2d& v1, const Vector2d& v2) {
		return (v1.x == v2.x && v1.y == v2.y);
	}
	
	friend bool operator!=(Vector2d& v1, const Vector2d& v2) {
		return !(v1.x == v2.x && v1.y == v2.y);
	}

	Vector2d operator/(float scalar) {
		return Vector2d(x / scalar, y / scalar);
	}

	Vector2d& operator/=(float scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}

	void normalize() {
		float l = length();
		if ( l > 0) { // we never want to attempt to divide by 0
			(*this) *= 1 / l;
		}
	}

	float x;
	float y;

};

#endif