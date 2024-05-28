#include <iostream>
#include "SharedPtr.hpp"

int main()
{
	SharedPtr<int> ptr(new int(5));
	SharedPtr<int> ptr2 = ptr;
	std::cout << *ptr << std::endl;
}