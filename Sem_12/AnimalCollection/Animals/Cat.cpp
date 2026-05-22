#include "Cat.h"

void Cat::sayHello() const 
{
	std::cout << "Hello, I am a cat!" << std::endl;
}

Animal* Cat::clone() const 
{
	return new Cat(*this);
}