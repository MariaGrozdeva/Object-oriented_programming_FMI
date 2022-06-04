#include "Farm.h"
#include <cassert>

void Farm::addAnimal(const Animal& currentAnimal)
{
	if (count == capacity)
		resize();
	animals[count++] = currentAnimal.clone();
}
bool Farm::addAnimal(Animal::AnimalType animalType)
{
	Animal* newAnimal = factory.createAnimal(animalType);

	if (newAnimal)
	{
		if (count == capacity)
			resize();
		animals[count++] = newAnimal;
	}

	return newAnimal != nullptr;
}

void Farm::allSayHello() const
{
	for (size_t i = 0; i < count; i++)
		animals[i]->sayHello();
}

size_t Farm::getCount() const
{
	return count;
}

Animal* Farm::operator[](size_t index)
{
	assert(index < count);
	return animals[index];
}
const Animal* Farm::operator[](size_t index) const
{
	assert(index < count);
	return animals[index];
}

Farm::Farm()
{
	capacity = 8;
	count = 0;
	animals = new Animal * [capacity];
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

void Farm::free()
{
	for (size_t i = 0; i < count; i++)
		delete animals[i];
	delete[] animals;
}
void Farm::copyFrom(const Farm& other)
{
	count = other.count;
	capacity = other.capacity;

	animals = new Animal * [capacity];

	for (size_t i = 0; i < count; i++)
		animals[i] = other.animals[i]->clone();
}

void Farm::resize()
{
	Animal** resizedCollection = new Animal * [capacity *= 2];

	for (size_t i = 0; i < count; i++)
		resizedCollection[i] = animals[i];

	delete[] animals;
	animals = resizedCollection;
}