#include "UniquePtrOfA.h"
#include <iostream>

void print(const UniquePtrOfA& ptr)
{
	std::cout << (*ptr).a << " " << (*ptr).b << std::endl;
}

int main()
{
	UniquePtrOfA ptr(new A());
	UniquePtrOfA other(std::move(ptr));
	print(other);
	std::cout << other->a << std::endl;
}
