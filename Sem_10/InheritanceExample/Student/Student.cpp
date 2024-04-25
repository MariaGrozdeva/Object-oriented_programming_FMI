#pragma warning(disable : 4996)
#include "Student.h"
#include <cstring>

Student::Student(const char* name, unsigned age, const char fn[10], const Gradebook& grades) 
	: Person(name, age)
{
	strcpy(this->fn, fn);
	this->grades = grades;
}

const char* Student::getFn() const
{
	return fn;
}

const Gradebook& Student::getGrades() const
{
	return grades;
}


