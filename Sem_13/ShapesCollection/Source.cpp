#include "ShapeCollection.h"

int main()
{
	ShapeCollection s;

	s.addCircle(3, 4, 1);
	s.addRectangle(1, 1, 9, 9);
	s.addTriangle(1, 2, 9, 4, 0, 0);

	std::cout << s.getIfPointIsInShapeByIndex(0, 3, 4.5) << std::endl;
	std::cout << s.getAreaOfFigureByIndex(2) << std::endl;
}