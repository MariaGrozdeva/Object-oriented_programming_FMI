#include "ShapeCollection/ShapeCollection.h"

int main()
{
	ShapeCollection shapeCollection;

	shapeCollection.addCircle(3, 4, 1);
	shapeCollection.addRectangle(1, 1, 9, 9);
	shapeCollection.addTriangle(1, 2, 9, 4, 0, 0);

	std::cout << "Perimeters of the figures:" << std::endl;
	for (size_t i = 0; i < shapeCollection.size(); i++)
	{
		std::cout << "Figure " << i << ": " << shapeCollection.getPerimeterOfFigureByIndex(i) << std::endl;
	}
	std::cout << std::endl << "Areas of the figures:" << std::endl;
	for (size_t i = 0; i < shapeCollection.size(); i++)
	{
		std::cout << "Figure " << i << ": " << shapeCollection.getAreaOfFigureByIndex(i) << std::endl;
	}
	std::cout << std::endl << "Check if point (3,3) is in figure i:" << std::endl;
	for (size_t i = 0; i < shapeCollection.size(); i++)
	{
		std::cout << "Figure " << i << ": " << shapeCollection.getIsPointInFigureByIndex(i, 3, 3) << std::endl;
	}
}
