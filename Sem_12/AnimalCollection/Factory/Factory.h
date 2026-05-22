#pragma once
#include "../Animals/Animal.h"

class AnimalFactory
{
public:
	static Animal* createAnimal(Animal::AnimalType animalType);
};