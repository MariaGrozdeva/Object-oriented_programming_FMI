#pragma once
#include "Person.h"
class Teacher : public Person
{
	Teacher() = default;
	Teacher(const char* name, unsigned age, const char** subjects, unsigned subjectsCount);
	Teacher(const Teacher& other);
	Teacher& operator=(const Teacher& other);
	Teacher(Teacher&& other) noexcept;
	Teacher& operator=(Teacher&& other) noexcept;
	~Teacher();

	void addSubject(const char* newSubject);
	void removeSubject(unsigned index);
	
	unsigned getSubjectsCount() const;
	unsigned getSubjectsCapacity() const;

	char** getSubjects() const;

	const char* operator[](unsigned index) const;
	char* operator[](unsigned index);

private:
	char** subjects;
	unsigned subjectsCount;
	unsigned subjectsCapacity;

	void free();
	void copyFrom(const Teacher& other);
	void moveFrom(Teacher&& other);
	void resize(unsigned newSize);
};

