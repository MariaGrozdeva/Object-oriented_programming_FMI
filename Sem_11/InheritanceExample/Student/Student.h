#pragma once
#include "Person.h"

class Student : public Person
{
private:
	size_t fn;

public:
	Student(const char* name, size_t age, size_t fn);

	void setFn(size_t fn);
	size_t getFn() const;
};