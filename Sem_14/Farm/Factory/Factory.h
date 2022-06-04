#pragma once
#include "Animal.h"

class AnimalFactory
{
public:
	virtual Animal* createAnimal(Animal::AnimalType animalType) const;
};
