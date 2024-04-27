#pragma once
#include "Person.h"
class Teacher : public Person
{
public:
	Teacher(const char* name, unsigned age, const char* const* subjects, size_t count);

	Teacher(const Teacher& other);
	Teacher(Teacher&& other) noexcept;

	Teacher& operator=(const Teacher& other);
	Teacher& operator=(Teacher&& other) noexcept;

	~Teacher();

	void setSubjects(const char* const* subjects, size_t count);
	void print() const;
private:
	char** subjects;
	size_t count;

	void free();
	void copyFrom(const Teacher& other);
	void moveFrom(Teacher&& other);
};

