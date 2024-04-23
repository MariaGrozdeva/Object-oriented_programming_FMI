#pragma once
#include "Person.h"

class Student : public Person
{
private:
	unsigned int fn;

public:
	Student(const char* name, unsigned int age, unsigned int fn);

	void setFn(unsigned int fn);
	unsigned int getFn() const;
};
