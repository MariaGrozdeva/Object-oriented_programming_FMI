#include "ShapeCollection.h"
#include "../ShapeFactory/ShapeFactory.h"
#include <stdexcept>

bool ShapeCollection::addShape(int shapeType)
{
    	Shape* newShape = ShapeFactory::createShape(shapeType);
	if (newShape)
	{
		if (count == capacity)
		{
			resize();
		}
		shapes[count++] = newShape;
	}
	return newShape;
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

int ShapeCollection::getShapeTypeByIndex(unsigned index) const
{
    	if (index >= count)
	{
		throw std::out_of_range("Index is out of range!");
	}
	return shapes[index]->getShapeType();
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
