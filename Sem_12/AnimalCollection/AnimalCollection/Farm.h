#pragma once
#include "../Animals/Animal.h"

class Farm
{
public:
	Farm();
	Farm(const Farm& other);
	Farm& operator=(const Farm& other);
	~Farm();

	bool addAnimal(Animal::AnimalType animalType);

	void allSayHello() const;

	Animal* operator[](unsigned index);
	const Animal* operator[](unsigned index) const;

	size_t size() const;

private:
	Animal** animals;

	size_t count = 0;
	size_t capacity = 8;

	void copyFrom(const Farm& other);
	void free();
	void resize();
};
