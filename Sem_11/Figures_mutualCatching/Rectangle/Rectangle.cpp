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

bool Rectangle::isPointInFigure(int x, int y) const
{
	Shape::Point p(x, y);
	return p.x >= getPointAtIndex(0).x && p.x <= getPointAtIndex(1).x &&
		p.y >= getPointAtIndex(0).y && p.y <= getPointAtIndex(2).y;
}

bool Rectangle::intersectsWith(const Shape* other) const
{
	return other->intersectsWithRectangle(this);
}

bool Rectangle::intersectsWithCircle(const Circle* other) const
{
	std::cout << "Formula for rectangle with circle" << std::endl;
	return true;
}

bool Rectangle::intersectsWithTriangle(const Triangle* other) const
{
	std::cout << "Formula for rectangle with triangle" << std::endl;
	return true;
}

bool Rectangle::intersectsWithRectangle(const Rectangle* other) const
{
	std::cout << "Formula for rectangle with rectangle" << std::endl;
	return true;
}
