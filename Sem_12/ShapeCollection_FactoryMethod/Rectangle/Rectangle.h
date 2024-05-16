#pragma once
#include "../Shape/Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(int x1, int y1, int x3, int y3);

	virtual double getArea() const override;
	virtual bool isPointInFigure(int x, int y) const override;

	virtual Shape* clone() const override;
};
