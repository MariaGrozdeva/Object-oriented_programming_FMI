#include "Person.h"
#include <cstring>

#pragma warning (disable : 4996)

Person::Person(const char* name, unsigned int age)
{
	setName(name);
	setAge(age);
}

Person::Person() : name(nullptr), age(0) {}

Person::Person(const Person& other) : name(nullptr)
{
    if (other.name != nullptr)
    {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
	age = other.age;
}

Person& Person::operator=(const Person& other)
{
    if (this != &other)
    {
		char* newName = nullptr;
        if (other.name != nullptr)
        {
            newName = new char[strlen(other.name) + 1];
            strcpy(newName, other.name);
        }

        delete[] name;
        name = newName;
        age = other.age;
    }
    return *this;
}

Person::~Person()
{
	delete[] name;
}

void Person::setName(const char* name)
{
	if (name == nullptr || this->name == name)
	{
		return;
	}

	char* tempName = new char[strlen(name) + 1]; // if new fails, this->name remains unchanged
	delete[] this->name;
	this->name = tempName;
	strcpy(this->name, tempName);
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
