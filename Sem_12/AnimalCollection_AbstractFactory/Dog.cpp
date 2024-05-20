#include "Dog.h"
#include <stdexcept>

Dog::Dog(const std::string& breed)
{
    this->breed = breed;
}

void Dog::sayHello() const 
{
	std::cout << "Hello, I am a dog! My breed is " << breed << std::endl;
}

Animal* Dog::clone() const 
{
	return new Dog(*this);
}

const char* Dog::getBreed() const
{
    return breed.c_str();
}

DogCreator::DogCreator() : AnimalCreator("dog")
{}

Animal* DogCreator::createAnimal(std::istream& is) const
{
    	std::string breed;
    	is >> breed;
    	return new Dog(breed);
}

static DogCreator __;
