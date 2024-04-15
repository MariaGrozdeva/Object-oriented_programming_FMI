#include "ObjectCounter.h"
#include <iostream>

int main()
{
	ObjectCounter obj1;
	ObjectCounter obj2;
	ObjectCounter obj3;

	{
		ObjectCounter obj4;
		ObjectCounter obj5;
		std::cout << "Current number of objects is: " << ObjectCounter::getObjectCount() << std::endl;
	}
	std::cout << "Current number of objects is: " << ObjectCounter::getObjectCount() << std::endl;
}