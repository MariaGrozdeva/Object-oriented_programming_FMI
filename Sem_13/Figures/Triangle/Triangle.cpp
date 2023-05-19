#include "Triangle.h"

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : Shape(3)
{
	setPoint(0, x1, y1);
	setPoint(1, x2, y2);
	setPoint(2, x3, y3);
}

double Triangle::getArea() const
{
	const Point& p1 = getPointAtIndex(0);
	const Point& p2 = getPointAtIndex(1);
	const Point& p3 = getPointAtIndex(2);
	
	double semiPer = getPerimeter() / 2;
	return sqrt(semiPer * (semiPer - p1.getDist(p2)) * (semiPer - p2.getDist(p3)) * (semiPer - p3.getDist(p1)));
}
double Triangle::getPerimeter() const
{
	const Point& p1 = getPointAtIndex(0);
	const Point& p2 = getPointAtIndex(1);
	const Point& p3 = getPointAtIndex(2);

	return p1.getDist(p2) + p2.getDist(p3) + p3.getDist(p1);
}
