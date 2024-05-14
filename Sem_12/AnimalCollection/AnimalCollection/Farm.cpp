#include "Farm.h"
#include "../Factory/Factory.h"
#include <cassert>

bool Farm::addAnimal(Animal::AnimalType animalType)
{
	Animal* newAnimal = AnimalFactory::createAnimal(animalType);

	if (newAnimal)
	{
		if (count == capacity)
		{
			resize();
		}
		animals[count++] = newAnimal;
	}

	return newAnimal;
}

void Farm::allSayHello() const
{
	for (size_t i = 0; i < count; i++)
	{
		animals[i]->sayHello();
	}
}

Animal* Farm::operator[](unsigned index)
{
	assert(index < count);
	return animals[index];
}
const Animal* Farm::operator[](unsigned index) const
{
	assert(index < count);
	return animals[index];
}

size_t Farm::size() const
{
	return count;
}

Farm::Farm()
{
	animals = new Animal * [capacity] {nullptr};
}
Farm::Farm(const Farm& other)
{
	copyFrom(other);
}
Farm& Farm::operator=(const Farm& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Farm::~Farm()
{
	free();
}

void Farm::copyFrom(const Farm& other)
{
	count = other.count;
	capacity = other.capacity;

	animals = new Animal * [capacity];
	for (size_t i = 0; i < count; i++)
	{
		animals[i] = other.animals[i]->clone();
	}
}
void Farm::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete animals[i];
	}
	delete[] animals;
}
void Farm::resize()
{
	Animal** resizedCollection = new Animal * [capacity *= 2];

	for (size_t i = 0; i < count; i++)
	{
		resizedCollection[i] = animals[i];
	}

	delete[] animals;
	animals = resizedCollection;
}
