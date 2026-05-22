#pragma once
#include "../Shape/Shape.h"

class Circle : public Shape
{
public:
	Circle(int x, int y, double radius);

	virtual double getArea() const override;
	virtual double getPerimeter() const override;
	virtual bool isPointInFigure(int x, int y) const override;
	
	virtual bool intersectsWith(const Shape* other) const override;
	virtual bool intersectsWithCircle(const Circle* other) const override;
	virtual bool intersectsWithTriangle(const Triangle* other) const override;
	virtual bool intersectsWithRectangle(const Rectangle* other) const override;

private:
	double radius;
};
