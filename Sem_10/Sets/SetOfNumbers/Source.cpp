#include "SetOfNumbers.h"

int main()
{
	SetOfNumbers set1(8);
	for (size_t i = 0; i <= 8; i++)
	{
		set1.add(i);
	}
	std::cout << "Elements of set1: " << set1 << std::endl;

	set1.remove(0);
	set1.remove(8);
	set1.remove(4);
	std::cout << "Elements of set1 after removing 0,4,8: " << set1 << std::endl;

	SetOfNumbers set2(8);
	set2.add(8);
	set2.add(0);
	std::cout << "Elements of set2: " << set2 << std::endl;

	std::cout << "Union of set1 and set2 is " << setUnion(set1, set2) << std::endl;
}