#include "Student.h"

Student::Student(const char* name, unsigned int age, unsigned int fn)
    : Person(name, age), fn(fn) {}

Student::Student()
    : Person(), fn(0) {}

void Student::setFn(unsigned int fn)
{
    this->fn = fn;
}

unsigned int Student::getFn() const
{
    return fn;
}

void Student::print() const
{
    Person::print();
    std::cout << "FN: " << fn << std::endl;
}
