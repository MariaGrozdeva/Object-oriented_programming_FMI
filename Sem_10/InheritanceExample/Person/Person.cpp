#pragma warning (disable: 4996)
#include <iostream>
#include "Person.h"
#include <cstring>

void Person::copyFrom(const Person& other)
{
	char* temp = new char[strlen(other.name) + 1];
	strcpy(temp, other.name);
	delete[] name;

	name = temp;
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

Person::Person(const char* name, unsigned age)
	: name(nullptr), age(0)
{
	try
	{
		setName(name);
		setAge(age);
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "Bad alloc occured in Person(name, age) ctor. Object not created\n";
		throw e;
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "Invalid argument occured in Person(name, age). Memory for name is released and the object will not be created\n";
		throw e;
	}
}

Person::Person(const Person& other)
{
	copyFrom(other);
}

Person& Person::operator=(const Person& other)
{
	if (this != &other)
	{
		//delete[] name is performed in copyFrom
		copyFrom(other);
	}

	return *this;
}

Person::Person(Person&& other) noexcept
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
		throw std::invalid_argument("String for the new name was nullptr");
	}

	char* temp = new char[strlen(newName) + 1];
	strcpy(temp, newName);
	delete[] name;
	name = temp;
}

void Person::setAge(unsigned newAge)
{
	if (newAge > 110)
		throw std::invalid_argument("Invalid value for age");

	age = newAge;
}

void Person::print() const
{
	std::cout << "Person: " << name << " age: " << age << std::endl;
}
