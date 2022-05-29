#pragma once
#pragma warning (disable : 4996)
#include <iostream>

class Person
{
private:
	char* name;
	size_t age;

	void copyFrom(const Person& other);
	void free();

public:
	Person(const char* name, size_t age);

	Person();
	Person(const Person& other);
	Person& operator=(const Person& other);
	~Person();

	void setName(const char* name);
	void setAge(size_t age);

	const char* getName() const;
	size_t getAge() const;

	void print() const;
};