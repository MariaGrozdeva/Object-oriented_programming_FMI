#include "Rectangle.h"

Rectangle::Rectangle(int x1, int y1, int x3, int y3) : Shape(4)
{
	setPoint(0, x1, y1);
	setPoint(1, x3, y1);
	setPoint(2, x3, y3);
	setPoint(3, x1, y3);
}

double Rectangle::getArea() const
{
	const Point& p1 = getPointAtIndex(0);
	const Point& p2 = getPointAtIndex(1);
	const Point& p3 = getPointAtIndex(2);

	return p1.getDist(p2) * p2.getDist(p3);
}
double Rectangle::getPerimeter() const
{
	const Point& p1 = getPointAtIndex(0);
	const Point& p2 = getPointAtIndex(1);
	const Point& p3 = getPointAtIndex(2);

	return 2 * (p1.getDist(p2) + p2.getDist(p3));
}
