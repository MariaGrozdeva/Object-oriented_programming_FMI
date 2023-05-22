#include "Shape.h"

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