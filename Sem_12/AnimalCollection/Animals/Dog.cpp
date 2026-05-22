#include "Dog.h"

void Dog::sayHello() const 
{
	std::cout << "Hello, I am a dog!" << std::endl;
}

Animal* Dog::clone() const
{
	return new Dog(*this);
}