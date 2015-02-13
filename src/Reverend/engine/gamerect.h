#pragma once
#ifndef GAMERECT_H
#define GAMERECT_H

class GameRect {
public:
	GameRect() : x(0), y(0), w(0), h(0) {}

	GameRect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {
	}

	void setPosition(int x, int y) { this->x = x, this->y = y; }
	
	GameRect operator+(const GameRect& v2) const {
		return GameRect(x + v2.x, y + v2.y, w + v2.w, h + v2.h);
	}
	
	GameRect operator-(const GameRect& v2) const {
		return GameRect(x - v2.x, y - v2.y, w - v2.w, h - v2.h);
	}

	int x;
	int y;
	int w;
	int h;
};

#endif;