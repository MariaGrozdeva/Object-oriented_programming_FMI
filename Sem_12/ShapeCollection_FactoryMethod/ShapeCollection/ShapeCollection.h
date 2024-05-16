#pragma once
#include "../Shape/Shape.h"

class ShapeCollection
{
public:
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection& operator=(const ShapeCollection& other);
	~ShapeCollection();
	
	bool addShape(int shapeType);

	double getAreaOfFigureByIndex(unsigned index) const;
	double getPerimeterOfFigureByIndex(unsigned index) const;
	double getIsPointInFigureByIndex(unsigned index, int x, int y) const;
	
	int getShapeTypeByIndex(unsigned index) const;

	size_t size() const;

private:
	Shape** shapes;
	size_t count = 0;
	size_t capacity = 8;

	void copyFrom(const ShapeCollection& other);
	void free();
	void resize();
};
