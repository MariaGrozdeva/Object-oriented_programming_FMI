#include "Circle/Circle.h"
#include "Triangle/Triangle.h"
#include "Rectangle/Rectangle.h"

void printIfPointsIntersect(const Shape* const* shapes, size_t shapesCount)
{
	for (size_t i = 0; i < shapesCount - 1; i++)
	{
		shapes[i]->intersectsWith(shapes[i + 1]);
	}
}

void freeCollection(Shape** shapes, size_t shapesCount)
{
	for (int i = 0; i < shapesCount; i++)
	{
		delete shapes[i];
	}
	delete[] shapes;
}

int main()
{
	Shape** arr = new Shape * [4];

	arr[0] = new Circle(3, 3, 4);
	arr[1] = new Circle(1, 4, 5);
	arr[2] = new Triangle(-2, -3, 1, -3, 1, 0);
	arr[3] = new Rectangle(3, 4, 6, 8);

	std::cout << "Intersection of points:" << std::endl;
	printIfPointsIntersect(arr, 4);

	freeCollection(arr, 4);
}
