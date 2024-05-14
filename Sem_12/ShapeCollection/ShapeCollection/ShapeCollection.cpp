#include "ShapeCollection.h"
#include "../Circle/Circle.h"
#include "../Rectangle/Rectangle.h"
#include "../Triangle/Triangle.h"
#include <stdexcept>

void ShapeCollection::addShape(Shape* shape)
{
	if (count == capacity)
	{
		resize();
	}
	shapes[count++] = shape;
}

void ShapeCollection::addCircle(int x1, int y1, double radius)
{
	addShape(new Circle(x1, y1, radius));
}
void ShapeCollection::addRectangle(int x1, int y1, int x3, int y3)
{
	addShape(new Rectangle(x1, y1, x3, y3));
}
void ShapeCollection::addTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	addShape(new Triangle(x1, y1, x2, y2, x3, y3));
}

double ShapeCollection::getAreaOfFigureByIndex(unsigned index) const
{
	if (index >= count)
	{
		throw std::out_of_range("Index is out of range!");
	}
	return shapes[index]->getArea();
}
double ShapeCollection::getPerimeterOfFigureByIndex(unsigned index) const
{
	if (index >= count)
	{
		throw std::out_of_range("Index is out of range!");
	}
	return shapes[index]->getPerimeter();
}
double ShapeCollection::getIsPointInFigureByIndex(unsigned index, int x, int y) const
{
	if (index >= count)
	{
		throw std::out_of_range("Index is out of range!");
	}
	return shapes[index]->isPointInFigure(x, y);
}

size_t ShapeCollection::size() const
{
	return count;
}

ShapeCollection::ShapeCollection()
{
	shapes = new Shape * [capacity] {nullptr};
}
ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
	copyFrom(other);
}
ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
ShapeCollection::~ShapeCollection()
{
	free();
}

void ShapeCollection::copyFrom(const ShapeCollection& other)
{
	count = other.count;
	capacity = other.capacity;

	shapes = new Shape * [capacity];
	for (size_t i = 0; i < count; i++)
	{
		shapes[i] = other.shapes[i]->clone();
	}
}
void ShapeCollection::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete shapes[i];
	}
	delete[] shapes;
}
void ShapeCollection::resize()
{
	Shape** newCollection = new Shape * [capacity *= 2];

	for (size_t i = 0; i < count; i++)
	{
		newCollection[i] = shapes[i];
	}

	delete[] shapes;
	shapes = newCollection;
}
