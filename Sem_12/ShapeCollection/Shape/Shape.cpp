#include "Shape.h"
#include <cassert>

double Shape::getPerimeter() const
{
    	assert(pointsCount >= 3);
    
    	double perimeter = 0;
    	for (size_t i = 0; i < pointsCount - 1; i++)
    	{
        	perimeter += points[i].getDist(points[i + 1]);
    	}
    	perimeter += points[pointsCount - 1].getDist(points[0]);
    	return perimeter;
}

void Shape::setPoint(unsigned index, int x, int y)
{
	if (index >= pointsCount)
	{
		throw std::out_of_range("Invalid index!");
	}
	points[index] = Point(x, y);
}

const Shape::Point& Shape::getPointAtIndex(unsigned index) const
{
	if (index >= pointsCount)
	{
		throw std::out_of_range("Invalid index!");
	}
	return points[index];
}

Shape::Shape(size_t pointsCount)
{
	this->pointsCount = pointsCount;
	points = new Point[pointsCount];
}

Shape::Shape(const Shape& other)
{
	copyFrom(other);
}
Shape& Shape::operator=(const Shape& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
Shape::~Shape()
{
	free();
}

void Shape::copyFrom(const Shape& other)
{
	pointsCount = other.pointsCount;
	points = new Point[pointsCount];
	for (size_t i = 0; i < pointsCount; i++)
	{
		points[i] = other.points[i];
	}
}
void Shape::free()
{
	delete[] points;
	points = nullptr;
}
