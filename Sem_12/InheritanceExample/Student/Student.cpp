#include "Student.h"

Student::Student(const char* name, unsigned int age, unsigned int fn) : Person(name, age)
{
	setFn(fn);
}

void Student::setFn(unsigned int fn)
{
	this->fn = fn;
}
unsigned int Student::getFn() const
{
	return fn;
}
