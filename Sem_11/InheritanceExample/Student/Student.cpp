#include "Student.h"

Student::Student(const char* name, size_t age, size_t fn) : Person(name, age)
{
	setFn(fn);
}

void Student::setFn(size_t fn)
{
	this->fn = fn;
}
size_t Student::getFn() const
{
	return fn;
}