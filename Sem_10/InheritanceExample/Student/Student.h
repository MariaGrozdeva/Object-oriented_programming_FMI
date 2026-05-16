#pragma once
#include "../Person/Person.h"

class Student : public Person
{
private:
    unsigned int fn;

public:
    Student(const char* name, unsigned int age, unsigned int fn);
    Student();

    void setFn(unsigned int fn);
    unsigned int getFn() const;
    void print() const;
};
