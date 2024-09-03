#pragma once
#include "Person.h"
class Student : public Person
{
public:
	Student(const char* name, unsigned age, unsigned fn);

	void setFacNumber(unsigned fn);
	unsigned getFacNumber() const;

	void print() const;
private:
	unsigned fn;

	bool isValidFn(unsigned fn);// faculty number is valid if its length is 5
};

