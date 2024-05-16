#include "ShapeCollection/ShapeCollection.h"

int main()
{
	ShapeCollection coll;

	while (true)
	{
	    	std::cout << std::endl << "Enter shape type: " << std::endl;
		int shapeType;
		std::cin >> shapeType;

		bool result = coll.addShape(shapeType);

		if (result)
		{
			#ifdef _WIN32
                		system("cls");
            		#else
                		system("clear");
            		#endif

			std::cout << "Current number of shapes in the collection: " << coll.size() << std::endl;

			std::cout << "Their areas:" << std::endl;
			for (size_t i = 0; i < coll.size(); i++)
			{
				std::cout << coll.getAreaOfFigureByIndex(i) << std::endl;
			}
		}
		else
		{
			std::cout << "Invalid shape type!" << std::endl;
		}
	}
}
