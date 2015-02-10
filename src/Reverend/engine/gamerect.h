#pragma once
#ifndef GAMERECT_H
#define GAMERECT_H

class GameRect {
public:
	GameRect() : x_(0), y_(0), w_(0), h_(0) {}

	GameRect(int x, int y, int w, int h) : x_(x), y_(y), w_(w), h_(h) {
	}

	void setPosition(int x, int y) { x_ = x, y_ = y; }
	int getX() { return x_; }
	int getY() { return y_; }
	int getWidth() { return w_; }
	int getHeight() { return h_;} 
	
	GameRect operator+(const GameRect& v2) const {
		return GameRect(x_ + v2.x_, y_ + v2.y_, w_ + v2.w_, h_ + v2.h_);
	}
	
	GameRect operator-(const GameRect& v2) const {
		return GameRect(x_ - v2.x_, y_ - v2.y_, w_ - v2.w_, h_ - v2.h_);
	}

private:
	int x_;
	int y_;
	int w_;
	int h_;
};

#endif;