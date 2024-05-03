#include "Person.h"

Person::Person(const char* name, unsigned int age) {
	setName(name);
	setAge(age);
}

void Person::setName(const char* name) {
	if (name == nullptr || this->name == name) {
		return;
	}
	delete[]this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
void Person::setAge(unsigned int age) {
	this->age = age;
}

Person::Person(const Person& other) {
	copyFrom(other);
}

Person::Person(Person&& other) noexcept {
	moveFrom(std::move(other));
}


Person& Person::operator=(const Person& other) {
	if (this != &other) {
		free();
		strcpy(name, other.name);
	}
	return *this;
}
Person& Person::operator=(Person&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}


Person::~Person() {
	free();
}

void Person::copyFrom(const Person& other) {
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	age = other.age;

}

void Person::moveFrom(Person&& other)  {
	name = other.name;
	other.name = nullptr;
	age = other.age;
	other.age = 0;
}

void Person::free() {
	delete[]name;
	name = nullptr;
}

const char* Person::getName() const{
	return name;
}
unsigned int Person::getAge() const{
	return age;	
}

void Person::print() const
{
	std::cout << "Name: " << name << ", Age: " << age << std::endl;
}
