#include "ShapeCollection.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

void ShapeCollection::addShape(Shape* shape)
{
	if (count == capacity)
		resize();
	shapes[count++] = shape;
}

void ShapeCollection::addCircle(int x1, int y1, double radius)
{
	Circle* circlce = new Circle(x1, y1, radius);
	addShape(circlce);
}
void ShapeCollection::addRectangle(int x1, int y1, int x3, int y3)
{
	Rectangle* rectangle = new Rectangle(x1, y1, x3, y3);
	addShape(rectangle);
}
void ShapeCollection::addTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	Triangle* triangle = new Triangle(x1, y1, x2, y2, x3, y3);
	addShape(triangle);
}

double ShapeCollection::getAreaOfFigureByIndex(size_t ind) const
{
	if (ind >= count)
		throw std::out_of_range("Out of range in shapes collection!");
	return shapes[ind]->getArea();
}
double ShapeCollection::getPerimeterOfFigureByIndex(size_t ind) const
{
	if (ind >= count)
		throw std::out_of_range("Out of range in shapes collection!");
	return shapes[ind]->getPerimeter();
}
double ShapeCollection::getIfPointIsInShapeByIndex(size_t ind, int x, int y) const
{
	if (ind >= count)
		throw std::out_of_range("Out of range in shapes collection!");
	return shapes[ind]->isPointInShape(x, y);
}

ShapeCollection::ShapeCollection()
{
	capacity = 8;
	count = 0;
	shapes = new Shape * [capacity];
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

void ShapeCollection::free()
{
	for (size_t i = 0; i < count; i++)
		delete shapes[i]; 
	delete[] shapes;
}
void ShapeCollection::copyFrom(const ShapeCollection& other)
{
	count = other.count;
	capacity = other.capacity;

	shapes = new Shape * [capacity];

	for (size_t i = 0; i < count; i++)
		shapes[i] = other.shapes[i]->clone();
}

void ShapeCollection::resize()
{
	Shape** newCollection = new Shape * [capacity *= 2];

	for (size_t i = 0; i < count; i++)
		newCollection[i] = shapes[i];

	delete[] shapes;
	shapes = newCollection;
}