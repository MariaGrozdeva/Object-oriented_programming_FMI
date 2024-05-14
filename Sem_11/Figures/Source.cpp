#include "Circle/Circle.h"
#include "Triangle/Triangle.h"
#include "Rectangle/Rectangle.h"

void printAreas(const Shape* const* shapes, size_t shapesCount)
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		std::cout << shapes[i]->getArea() << std::endl;
	}
}

void printPerimeters(const Shape* const* shapes, size_t shapesCount)
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		std::cout << shapes[i]->getPerimeter() << std::endl;
	}
}

void printIfPointsAreInFigures(const Shape* const* shapes, size_t shapesCount)
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		std::cout << shapes[i]->isPointInFigure(i + 1, i + 3) << std::endl;
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

	std::cout << "Areas:" << std::endl;
	printAreas(arr, 4);
	
	std::cout << std::endl << "Perimeters:" << std::endl;
	printPerimeters(arr, 4);

	std::cout << std::endl << "Points in figures:" << std::endl;
	printIfPointsAreInFigures(arr, 4);

	freeCollection(arr, 4);
}
