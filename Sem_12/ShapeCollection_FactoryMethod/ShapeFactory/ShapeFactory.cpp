#include "ShapeFactory.h"
#include "../Circle/Circle.h"
#include "../Triangle/Triangle.h"
#include "../Rectangle/Rectangle.h"

Shape* ShapeFactory::createShape(int shapeType)
{
	switch (shapeType)
   	{
        case Circle::getCircleType():
        {
            	std::cout << "Enter data for Circle:" << std::endl;
            	int x, y;
            	double radius;
            	std::cin >> x >> y >> radius;
            	return new Circle(x, y, radius);
        }
        case Triangle::getTriangleType():
        {
            	std::cout << "Enter data for Triangle:" << std::endl;
            	int x1, y1, x2, y2, x3, y3;
            	std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            	return new Triangle(x1, y1, x2, y2, x3, y3);
        }
        case Rectangle::getRectangleType():
        {
            	std::cout << "Enter data for Rectangle:" << std::endl;
            	int x1, y1, x3, y3;
	        std::cin >> x1 >> y1 >> x3 >> y3;
            	return new Rectangle(x1, y1, x3, y3);
        }
        default:
            	return nullptr;
    	}
}
