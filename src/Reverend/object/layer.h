#pragma once
#ifndef LAYER_H
#define LAYER_H

class Layer
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void clean() = 0;
protected:
	virtual ~Layer() {}
};

#endif