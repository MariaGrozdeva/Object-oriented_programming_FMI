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

bool Circle::intersectsWith(const Shape* other) const
{
	return other->intersectsWithCircle(this);
}

bool Circle::intersectsWithCircle(const Circle* other) const
{
	std::cout << "Formula for circle with circle" << std::endl;
	return true;
}

bool Circle::intersectsWithTriangle(const Triangle* other) const
{
	std::cout << "Formula for circle with triangle" << std::endl;
	return true;
}

bool Circle::intersectsWithRectangle(const Rectangle* other) const
{
	std::cout << "Formula for circle with rectangle" << std::endl;
	return true;
}
