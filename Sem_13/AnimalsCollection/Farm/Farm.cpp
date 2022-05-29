#include "Farm.h"

void Farm::addAnimal(const Animal& currentAnimal)
{
	if (count == capacity)
		resize();
	animals[count++] = currentAnimal.clone();
}

void Farm::allSayHello() const
{
	for (size_t i = 0; i < count; i++)
		animals[i]->sayHello();
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