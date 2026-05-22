#include "Factory.h"
#include "../Animals/Cat.h"
#include "../Animals/Dog.h"
#include "../Animals/Mouse.h"

Animal* AnimalFactory::createAnimal(Animal::AnimalType animalType)
{
	switch (animalType)
	{
	case Animal::AnimalType::Cat: return new Cat();
	case Animal::AnimalType::Dog: return new Dog();
	case Animal::AnimalType::Mouse: return new Mouse();
	}

	return nullptr;
}