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
	Point p1 = getPointAtIndex(0);
	Point p2 = getPointAtIndex(1);
	Point p3 = getPointAtIndex(2);

	return p1.getDist(p2) * p2.getDist(p3);
}
double Rectangle::getPerimeter() const
{
	Point p1 = getPointAtIndex(0);
	Point p2 = getPointAtIndex(1);
	Point p3 = getPointAtIndex(2);

	return 2 * (p1.getDist(p2) + p2.getDist(p3));
}

bool Rectangle::isPointInShape(int x, int y) const
{
	Point p(x, y);
	return p.x >= getPointAtIndex(0).x && p.y >= getPointAtIndex(1).x && p.y <= getPointAtIndex(0).y && p.y >= getPointAtIndex(2).y;
}

Shape* Rectangle::clone() const
{
	return new Rectangle(*this);
}