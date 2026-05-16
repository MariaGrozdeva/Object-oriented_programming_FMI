#pragma once
#include <iostream>

class Person
{
private:
	char* name = nullptr;
	unsigned int age;

public:
	Person(const char* name, unsigned int age);

	Person();
	Person(const Person& other);
	Person& operator=(const Person& other);
	Person(Person&& other) noexcept;
	Person& operator=(Person&& other) noexcept;
	~Person();

	void setName(const char* name);
	void setAge(unsigned int age);

	const char* getName() const;
	unsigned int getAge() const;

	void print() const;
};
