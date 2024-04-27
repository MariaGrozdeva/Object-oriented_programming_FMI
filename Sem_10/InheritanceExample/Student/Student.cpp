#pragma warning (disable : 4996)
#include "Student.h"
#include <cstring>
#include <iostream>

Student::Student(const char* name, unsigned age, const char* fn, const Gradebook& gradeBook)
	: Person(name, age)
{
	if (!fn || strlen(fn) > 10)
		throw std::invalid_argument("Invalid fn! Object was not created");

	strcpy(this->fn, fn);
	this->gradeBook = gradeBook;
}

void Student::addGrade(unsigned newGrade)
{
	gradeBook.pushGrade(newGrade);
}

void Student::removeGradeAt(unsigned index)
{
	gradeBook.removeGrade(index);
}

void Student::removeGrade()
{
	gradeBook.popGrade();
}

const Gradebook& Student::getGrades() const
{
	return gradeBook;
}

void Student::print() const
{
	Person::print();
	std::cout << "Faculty_number: " << fn << ' ';
	gradeBook.print();
}
