#pragma once
#include "Animal.h"

class AnimalCollection
{
public:
	AnimalCollection();
	AnimalCollection(const AnimalCollection& other);
	AnimalCollection& operator=(const AnimalCollection& other);
	~AnimalCollection();

	void createAnimal(std::istream& is);

	void allSayHello() const;

	Animal* operator[](unsigned index);
	const Animal* operator[](unsigned index) const;

	size_t size() const;

private:
	Animal** animals;

	size_t count = 0;
	size_t capacity = 8;

	void copyFrom(const AnimalCollection& other);
	void free();
	void resize();
};