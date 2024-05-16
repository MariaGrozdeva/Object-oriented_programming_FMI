#pragma once
#include <iostream>
#include <cmath>

class Shape
{
public:
	Shape(size_t pointsCount, int shapeType);

	Shape(const Shape& other);
	Shape& operator=(const Shape& other);
	virtual ~Shape(); // !!

	void setPoint(unsigned index, int x, int y);

	virtual double getArea() const = 0; // pure virtual
	virtual double getPerimeter() const; // non-pure virtual
	virtual bool isPointInFigure(int x, int y) const = 0; // pure virtual

	virtual Shape* clone() const = 0;
	
	int getShapeType() const;
	
protected:
	struct Point
	{
		int x;
		int y;

		Point() : Point(0, 0)
		{}
		Point(int x, int y) : x(x), y(y) 
		{}

		double getDist(const Point& other) const
		{
			int distX = x - other.x;
			int distY = y - other.y;

			return sqrt(distX * distX + distY * distY);
		}
	};

	const Point& getPointAtIndex(unsigned index) const;

private:
	Point* points;
	size_t pointsCount;
	
	int shapeType;

	void copyFrom(const Shape& other);
	void free();
};
