#pragma once
#include "Person.h"

class Teacher : public Person
{
public:
	Teacher();
	Teacher(const char*, unsigned, const char* const*, size_t);
	Teacher(const Teacher&);
	Teacher(Teacher&&) noexcept;
	Teacher& operator=(const Teacher&);
	Teacher& operator=(Teacher&&) noexcept;
	~Teacher();

	void addSubject(const char*);
	void removeSubject(const char*);

private:
	void setSubjects(const char* const*, size_t);
	void free();
	void resize();

private:
	char** subjects;
	size_t subCount;
	size_t subCapacity;
};