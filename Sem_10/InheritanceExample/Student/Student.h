#pragma once
#include "Person.h"

class Student : public Person
{
public:
	Student();
	Student(const char*, unsigned, unsigned);

	unsigned getFn() const;

private:
	unsigned fn;
};

