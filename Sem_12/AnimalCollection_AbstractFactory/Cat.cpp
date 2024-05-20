#include "Cat.h"

void Cat::sayHello() const 
{
	std::cout << "Hello, I am a cat!" << std::endl;
}

Animal* Cat::clone() const 
{
	return new Cat(*this);
}

CatCreator::CatCreator() : AnimalCreator("cat")
{}

Animal* CatCreator::createAnimal(std::istream& is) const
{
    	return new Cat();
}

static CatCreator __;
