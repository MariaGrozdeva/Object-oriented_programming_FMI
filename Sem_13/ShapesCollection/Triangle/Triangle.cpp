#include "Triangle.h"

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : Shape(3)
{
	setPoint(0, x1, y1);
	setPoint(1, x2, y2);
	setPoint(2, x3, y3);
}

double Triangle::getArea() const
{
	Point p1 = getPointAtIndex(0);
	Point p2 = getPointAtIndex(1);
	Point p3 = getPointAtIndex(2);
	
	double semiPer = getPerimeter() / 2;

	return sqrt(semiPer * (semiPer - p1.getDist(p2)) * (semiPer - p2.getDist(p3)) * (semiPer - p3.getDist(p1)));
}
double Triangle::getPerimeter() const
{
	Point p1 = getPointAtIndex(0);
	Point p2 = getPointAtIndex(1);
	Point p3 = getPointAtIndex(2);

	return p1.getDist(p2) + p2.getDist(p3) + p3.getDist(p1);
}

bool Triangle::isPointInShape(int x, int y) const
{
	Point p(x, y);

	Triangle t1(getPointAtIndex(0).x, getPointAtIndex(0).y, getPointAtIndex(1).x, getPointAtIndex(1).y, p.x, p.y);
	Triangle t2(getPointAtIndex(2).x, getPointAtIndex(2).y, getPointAtIndex(1).x, getPointAtIndex(1).y, p.x, p.y);
	Triangle t3(getPointAtIndex(2).x, getPointAtIndex(2).y, getPointAtIndex(0).x, getPointAtIndex(0).y, p.x, p.y);

	return abs(t1.getArea() + t2.getArea() + t3.getArea() - getArea()) <= std::numeric_limits<double>::epsilon();
}

Shape* Triangle::clone() const
{
	return new Triangle(*this);
}