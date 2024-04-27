#pragma once
#pragma warning(disable:4996)
#include <iostream>
class Person
{
public:
	Person();
	Person(const char* name, unsigned age);

	Person(const Person& other);
	Person(Person&& other) noexcept;

	Person& operator=(const Person& other);
	Person& operator=(Person&& other) noexcept;

	~Person();

	void setName(const char* name);
	void setAge(unsigned age);

	const char* getName() const;
	unsigned getAge() const;

	void print() const;
private:
	char* name;
	unsigned age;

	void free();
	void moveFrom(Person&& other);
};

