#include "DynamicArrayOfPointers.h"

int main()
{
	DynamicArrayOfPointers dA;

	A obj1{ 5, 23 };
	A obj2{ 22, 24 };

	dA.addAtFirstFreeIndex(obj1);
	dA.addAtFirstFreeIndex(obj2);
	
	std::cout << dA[0].x;
}