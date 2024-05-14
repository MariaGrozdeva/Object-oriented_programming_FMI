#include "Circle.h"

namespace {
	const double pi = 3.1415;
}

Circle::Circle(int x, int y, double radius) : Shape(1)
{
	this->radius = radius;
	setPoint(0, x, y);
}

double Circle::getArea() const
{
	return pi * radius * radius;
}

double Circle::getPerimeter() const
{
	return 2 * pi * radius;
}

bool Circle::isPointInFigure(int x, int y) const
{
	Shape::Point p(x, y);
	return p.getDist(getPointAtIndex(0)) <= radius;
}

Shape* Circle::clone() const
{
	return new Circle(*this);
}
