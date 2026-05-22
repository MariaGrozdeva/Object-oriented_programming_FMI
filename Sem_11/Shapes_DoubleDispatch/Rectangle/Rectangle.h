#pragma once
#include "../Shape/Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(int x1, int y1, int x3, int y3);

	virtual double getArea() const override;
	virtual bool isPointInFigure(int x, int y) const override;
	
	virtual bool intersectsWith(const Shape* other) const override;
	virtual bool intersectsWithCircle(const Circle* other) const override;
	virtual bool intersectsWithTriangle(const Triangle* other) const override;
	virtual bool intersectsWithRectangle(const Rectangle* other) const override;
};
