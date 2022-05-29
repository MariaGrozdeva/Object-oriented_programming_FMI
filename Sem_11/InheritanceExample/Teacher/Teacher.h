#pragma once
#pragma warning (disable : 4996)
#include "Person.h"

class Teacher : public Person
{
private:
	char** subjects;
	size_t subjectsCount;

	void free();
	void copyFrom(const Teacher& other);

public:
	Teacher(const char* name, size_t age, const char* const* subjects, size_t subjectsCount);

	Teacher(const Teacher& other);
	Teacher& operator=(const Teacher& other);
	~Teacher();
};
