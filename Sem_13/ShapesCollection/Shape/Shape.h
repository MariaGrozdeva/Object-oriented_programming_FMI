#pragma once
#include <iostream>

class Shape
{
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

	const Point& getPointAtIndex(size_t index) const;

private:
	Point* points;
	size_t pointsCount;

	void copyFrom(const Shape& other);
	void free();

public:
	Shape(size_t pointsCount);

	Shape(const Shape& other);
	Shape& operator=(const Shape& other);
	virtual ~Shape(); // !!

	void setPoint(size_t index, int x, int y);

	virtual double getArea() const = 0; // pure virtual
	virtual double getPerimeter() const = 0; // pure virtual

	virtual bool isPointInShape(int x, int y) const = 0;

	virtual Shape* clone() const = 0;
};