#pragma once
#include "Person.h"

class Teacher : public Person
{
public:
	Teacher(const char* name, unsigned age, const char* const* subjects, unsigned subjectsCount);
	Teacher(const Teacher& other);
	Teacher& operator=(const Teacher& other);
	Teacher(Teacher&& other) noexcept;
	Teacher& operator=(Teacher&& other) noexcept;
	~Teacher();

	const char* const* getSubjects() const;
	unsigned getSubjectsCount() const;


	void addSubject(const char* subject);
	void removeSubjectAt(unsigned index);
	void removeSubject();

private:
	char** subjects;
	unsigned subjectsCount;
	unsigned capacity;

	void free();
	void copyFrom(const Teacher& other);
	void moveFrom(Teacher&& other);
	void resize(unsigned newCapacity);
	void setSubjects(const char* const* subjects, unsigned subjectsCount);
};

