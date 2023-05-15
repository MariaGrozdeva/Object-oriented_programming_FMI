#include "Teacher.h"

Teacher::Teacher(const char* name, unsigned int age, const char* const* subjects, unsigned int subjectsCount) : Person(name, age)
{
	this->subjectsCount = subjectsCount;
	this->subjects = new char* [subjectsCount];

	for (size_t i = 0; i < subjectsCount; i++)
	{
		this->subjects[i] = new char[strlen(subjects[i]) + 1];
		strcpy(this->subjects[i], subjects[i]);
	}
}

Teacher::Teacher(const Teacher& other) : Person(other)
{
	copyFrom(other);
}
Teacher& Teacher::operator=(const Teacher& other)
{
	if (this != &other)
	{
		Person::operator=(other);

		free();
		copyFrom(other);
	}

	return *this;
}
Teacher::~Teacher()
{
	free();
}

void Teacher::free()
{
	for (size_t i = 0; i < subjectsCount; i++)
	{
		delete[] subjects[i];
	}
	delete[] subjects;
	subjects = nullptr;
}
void Teacher::copyFrom(const Teacher& other)
{
	subjectsCount = other.subjectsCount;
	subjects = new char* [subjectsCount];

	for (size_t i = 0; i < subjectsCount; i++)
	{
		subjects[i] = new char[strlen(other.subjects[i]) + 1];
		strcpy(subjects[i], other.subjects[i]);
	}
}
