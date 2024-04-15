#include "Person.h"

Person::Person(const char* name, unsigned int age)
{
	setName(name);
	setAge(age);
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
Person::~Person()
{
	free();
}

void Person::setName(const char* name)
{
	if (name == nullptr || this->name == name)
	{
		return;
	}
	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
void Person::setAge(unsigned int age)
{
	this->age = age;
}

const char* Person::getName() const
{
	return name;
}
unsigned int Person::getAge() const
{
	return age;
}

void Person::print() const
{
	std::cout << "Name: " << name << ", Age: " << age << std::endl;
}

void Person::copyFrom(const Person& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	age = other.age;
}
void Person::free()
{
	delete[] name;
	name = nullptr;
}