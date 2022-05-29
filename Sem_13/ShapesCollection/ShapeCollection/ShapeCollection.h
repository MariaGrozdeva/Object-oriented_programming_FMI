#pragma once
#include "Shape.h"

class ShapeCollection
{
private:
	Shape** shapes;
	size_t capacity;
	size_t count;

	void free();
	void copyFrom(const ShapeCollection& other);

	void resize();

	void addShape(Shape* shape);

public:
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection& operator=(const ShapeCollection& other);
	~ShapeCollection();

	void addCircle(int x1, int y1, double radius);
	void addRectangle(int x1, int y1, int x3, int y3);
	void addTriangle(int x1, int y1, int x2, int y2, int x3, int y3);

	double getAreaOfFigureByIndex(size_t ind) const;
	double getPerimeterOfFigureByIndex(size_t ind) const;
	double getIfPointIsInShapeByIndex(size_t ind, int x, int y) const;
};