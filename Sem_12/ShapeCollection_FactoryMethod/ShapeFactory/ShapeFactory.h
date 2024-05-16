#pragma once
#include "../Shape/Shape.h"

class ShapeFactory
{
public:
	static Shape* createShape(int shapeType);
};
