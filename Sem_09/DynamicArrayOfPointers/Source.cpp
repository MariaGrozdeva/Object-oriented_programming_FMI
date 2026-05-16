#include "DynamicArrayOfPointers.h"

int main()
{
	DynamicArrayOfPointers dA;
	A obj1{5, 23};
	A obj2{22, 24};
	dA.addAtFirstFreeIndex(obj1);
	dA.addAtFirstFreeIndex(obj2);
	std::cout << dA[0].x << " " << dA[1].y << "\n";

	dA.removeAt(0);
	std::cout << "contains 0: " << dA.contains(0) << "\n";

	dA.setAtIndex(A{7, 8}, 0);
	std::cout << dA[0].x << "\n";

	DynamicArrayOfPointers dB(dA);
	std::cout << dB[0].x << "\n";

	DynamicArrayOfPointers dC(std::move(dB));
	std::cout << dC[0].x << "\n";

	return 0;
}
