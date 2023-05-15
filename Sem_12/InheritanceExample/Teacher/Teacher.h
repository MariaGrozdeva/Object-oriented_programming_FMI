#pragma once
#pragma warning (disable : 4996)
#include "Person.h"

class Teacher : public Person
{
private:
	char** subjects;
	unsigned int subjectsCount;

	void free();
	void copyFrom(const Teacher& other);

public:
	Teacher(const char* name, unsigned int age, const char* const* subjects, unsigned int subjectsCount);
	Teacher(const Teacher& other);
	Teacher& operator=(const Teacher& other);
	~Teacher();
};
