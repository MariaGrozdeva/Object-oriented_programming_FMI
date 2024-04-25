#pragma warning(disable: 4996)
#include "Person.h"
#include <cstring>
#include <iostream>

void Person::copyFrom(const Person& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	age = other.age;
}

void Person::moveFrom(Person&& other)
{
	name = other.name;
	age = other.age;

	other.name = nullptr;
	other.age = 0;
}

void Person::free()
{
	delete[] name;
	age = 0;
}

Person::Person(const char* name, unsigned age) : name(nullptr), age(0)
{
}

Person::Person(const Person& other)
{
	copyFrom(other);
}

Person& Person::operator=(const Person& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Person::Person(Person&& other) noexcept
	:name(nullptr), age(0)
{
	moveFrom(std::move(other));
}

Person& Person::operator=(Person&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Person::~Person()
{
	free();
}

const char* Person::getName() const
{
	return name;
}

unsigned Person::getAge() const
{
	return age;
}

void Person::setName(const char* newName)
{
	if (!newName)
	{
		std::cerr << "Invalid argument for name \n";
		return;
	}


	char* temp = new char[strlen(newName) + 1];
	strcpy(temp, newName);
	delete[] name;

	name = temp;
}

void Person::setAge(unsigned newAge)
{
	if (newAge > 110)
	{
		std::cerr << "Invalid argument for age \n";
		return;
	}

	age = newAge;
}
