#include "Student.h"
#include <iostream>

Student::Student() : fn(0)
{}

Student::Student(const char* name, unsigned age, unsigned fn) : Person(name, age), fn(fn)
{}

unsigned Student::getFn() const
{
	return fn;
}
