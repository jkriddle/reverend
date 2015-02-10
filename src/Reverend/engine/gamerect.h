#pragma once
#ifndef GAMERECT_H
#define GAMERECT_H

class GameRect {
public:
	GameRect() : x(0), y(0), width(0), height(0) {}

	GameRect(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {
	}

	void setPosition(int x, int y) { x = x, y = y; }
	
	GameRect operator+(const GameRect& v2) const {
		return GameRect(x + v2.x, y + v2.y, width + v2.width, height + v2.height);
	}
	
	GameRect operator-(const GameRect& v2) const {
		return GameRect(x - v2.x, y - v2.y, width - v2.width, height - v2.height);
	}

	int x;
	int y;
	int width;
	int height;
};

#endif;