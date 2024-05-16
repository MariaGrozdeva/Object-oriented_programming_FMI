#pragma once
#include "../Shape/Shape.h"

class ShapeCollection
{
public:
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection& operator=(const ShapeCollection& other);
	~ShapeCollection();

	void addCircle(int x1, int y1, double radius);
	void addRectangle(int x1, int y1, int x3, int y3);
	void addTriangle(int x1, int y1, int x2, int y2, int x3, int y3);

	double getAreaOfFigureByIndex(unsigned index) const;
	double getPerimeterOfFigureByIndex(unsigned index) const;
	double getIsPointInFigureByIndex(unsigned index, int x, int y) const;

	size_t size() const;

private:
	Shape** shapes;
	size_t count = 0;
	size_t capacity = 8;

	void copyFrom(const ShapeCollection& other);
	void free();
	void resize();

	void addShape(Shape* shape);
};
