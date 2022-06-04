#pragma once
#include "Animal.h"
#include "Factory.h"

class Farm
{
private:
	Animal** animals;
	size_t capacity;
	size_t count;

	void free();
	void copyFrom(const Farm& other);

	void resize();

	AnimalFactory factory;

public:
	Farm();
	Farm(const Farm& other);
	Farm& operator=(const Farm& other);
	~Farm();

	void addAnimal(const Animal& animal);
	bool addAnimal(Animal::AnimalType animalType);

	void allSayHello() const;

	size_t getCount() const;

	Animal* operator[](size_t index);
	const Animal* operator[](size_t index) const;
};