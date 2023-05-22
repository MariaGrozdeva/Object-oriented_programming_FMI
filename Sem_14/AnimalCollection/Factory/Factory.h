#pragma once
#include "../Animals/Animal.h"

class AnimalFactory
{
private:
	static AnimalFactory factory;

	AnimalFactory() = default;

public:
	AnimalFactory(const AnimalFactory&) = delete;
	AnimalFactory& operator=(const AnimalFactory&) = delete;

	static AnimalFactory& getInstance();

	virtual Animal* createAnimal(Animal::AnimalType animalType) const;
};