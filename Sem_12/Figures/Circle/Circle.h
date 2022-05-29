#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:
	double radius;

public:
	Circle(int x, int y, double radius);

	double getArea() const override;
	double getPerimeter() const override;
};