#pragma once
#include "Person.h"
#include "Gradebook.h"

class Student : public Person
{
	Student(const char* name, unsigned age, const char fn[10], const Gradebook& grades);

	const char* getFn() const;
	const Gradebook& getGrades() const;

private:
	char fn[10];
	Gradebook grades; // has grades. gradebook takes care of the marks of the student	
};

