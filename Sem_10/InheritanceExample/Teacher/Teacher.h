#pragma once
#pragma warning (disable : 4996)
#include "Person.h"

class Teacher: public Person
{

public:
	Teacher(const char*name, unsigned int age, const char* const* subjects, unsigned int subjectsCount);
	Teacher(const Teacher& other);
	Teacher(Teacher&& other) noexcept;
	Teacher& operator=(const Teacher& other);
	Teacher& operator=( Teacher&& other) noexcept;
	~Teacher();

	//void addAtFirstFreeIndex(const char* el);
	void removeAt(unsigned int index);
	void popBack();
	size_t size() const;
	bool contains(unsigned int index) const;
	void setAtIndex(const char* obj, unsigned int index);
	const char* operator[](unsigned int index) const;




private:
	char** subjects;
	unsigned int subjectsCount;
	unsigned int capacity;

	void free();
	void copyFrom(const Teacher& other);
	void moveFrom(Teacher&& other);

	void resize(unsigned int newCapacity);
	unsigned int getFirstFreeIndex() const;

};


