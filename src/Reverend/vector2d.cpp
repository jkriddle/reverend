#include "vector2d.h"

const Vector2d* Vector2d::NORTH = new Vector2d(0, 1);
const Vector2d* Vector2d::NORTH_EAST = new Vector2d(1, 1);
const Vector2d* Vector2d::EAST = new Vector2d(1, 0);
const Vector2d* Vector2d::SOUTH_EAST = new Vector2d(1, -1);
const Vector2d* Vector2d::SOUTH = new Vector2d(0, -1);
const Vector2d* Vector2d::SOUTH_WEST = new Vector2d(-1, -1);
const Vector2d* Vector2d::WEST = new Vector2d(-1, 0);
const Vector2d* Vector2d::NORTH_WEST = new Vector2d(-1, 0);