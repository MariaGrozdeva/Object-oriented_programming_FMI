#include "AnimalCollection.h"
#include "AnimalFactory.hpp"
#include <stdexcept>

void AnimalCollection::createAnimal(std::istream& is)
{
	Animal* newAnimal = AnimalFactory::getFactory().createAnimal(is);

	if (newAnimal)
	{
		if (count == capacity)
		{
			resize();
		}
		animals[count++] = newAnimal;
	}
}

void AnimalCollection::allSayHello() const
{
	for (size_t i = 0; i < count; i++)
	{
		animals[i]->sayHello();
	}
}

Animal* AnimalCollection::operator[](unsigned index)
{
	if (index >= count)
	{
	    throw std::out_of_range("Index is out of range");
	}
	return animals[index];
}
const Animal* AnimalCollection::operator[](unsigned index) const
{
	if (index >= count)
	{
	    throw std::out_of_range("Index is out of range");
	}
	return animals[index];
}

size_t AnimalCollection::size() const
{
	return count;
}

AnimalCollection::AnimalCollection()
{
	animals = new Animal * [capacity] {nullptr};
}
AnimalCollection::AnimalCollection(const AnimalCollection& other)
{
	copyFrom(other);
}
AnimalCollection& AnimalCollection::operator=(const AnimalCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
AnimalCollection::~AnimalCollection()
{
	free();
}

void AnimalCollection::copyFrom(const AnimalCollection& other)
{
	count = other.count;
	capacity = other.capacity;

	animals = new Animal * [capacity];
	for (size_t i = 0; i < count; i++)
	{
		animals[i] = other.animals[i]->clone();
	}
}
void AnimalCollection::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete animals[i];
	}
	delete[] animals;
}
void AnimalCollection::resize()
{
	Animal** resizedCollection = new Animal * [capacity *= 2];

	for (size_t i = 0; i < count; i++)
	{
		resizedCollection[i] = animals[i];
	}

	delete[] animals;
	animals = resizedCollection;
}