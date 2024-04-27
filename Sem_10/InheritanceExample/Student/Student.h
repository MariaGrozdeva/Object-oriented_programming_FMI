#pragma once
#include "Person.h"
#include "Gradebook.h"

class Student : public Person
{
public:
	Student() = default;
	Student(const char* name, unsigned age, const char* fn, const Gradebook& gradeBook);

	void addGrade(unsigned newGrade);
	void removeGradeAt(unsigned index);
	void removeGrade();

	const Gradebook& getGrades() const;
	void print() const;

private:
	static constexpr unsigned facultyNumberLen = 10;

	char fn[facultyNumberLen];
	Gradebook gradeBook;	
};

