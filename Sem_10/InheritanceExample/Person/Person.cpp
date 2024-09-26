#include "Person.h"
#include <iostream>
#pragma warning (disable : 4996)

Person::Person() : name(nullptr), age(0)
{
	setName("Name");
}

Person::Person(const char* name, unsigned age) : name(nullptr), age(age)
{
	setName(name);
}

Person::Person(const Person& other) : name(nullptr), age(other.age)
{
	setName(other.name);
}

Person::Person(Person&& other) noexcept
{
	name = other.name;
	age = other.age;
	
	other.name = nullptr;
	other.age = 0;
}

Person& Person::operator=(const Person& other)
{
	if (this == &other)
		return *this;

	char* tempName = new char[strlen(other.name) + 1];
	strcpy(tempName, other.name);
	delete[] this->name;
	this->name = tempName;
	this->age = other.age;

	return *this;
}

Person& Person::operator=(Person&& other) noexcept
{
	if (this == &other)
		return *this;

	delete[] name;
	name = other.name;
	age = other.age;
	other.name = nullptr;
	other.age = 0;

	return *this;
}

Person::~Person()
{
	delete[] name;
	name = nullptr;
	age = 0;
}

const char* Person::getName() const
{
	return name;
}

unsigned Person::getAge() const
{
	return age;
}

void Person::setName(const char* name)
{
	if (this->name == name || !name)
		return;

	char* tempName = new char[strlen(name) + 1];
	strcpy(tempName, name);
	delete[] this->name;
	this->name = tempName;
}