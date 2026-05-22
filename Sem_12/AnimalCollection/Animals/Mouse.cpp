#include "Mouse.h"

void Mouse::sayHello() const
{
	std::cout << "Hello, I am a mouse!" << std::endl;
}

Animal* Mouse::clone() const
{
	return new Mouse(*this);
}