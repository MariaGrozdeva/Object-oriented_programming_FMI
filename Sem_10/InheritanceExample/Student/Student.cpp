#include "Student.h"

Student::Student(const char* name, unsigned age, unsigned fn) : Person(name, age)
{
    setFacNumber(fn);
}

void Student::setFacNumber(unsigned fn)
{
    if (!isValidFn(fn))
    {
        throw std::invalid_argument("Invalid faculty number!");
    }
    this->fn = fn;
}

unsigned Student::getFacNumber() const
{
    return fn;
}

void Student::print() const
{
    std::cout << getName() << " " << getAge() << " " << fn << std::endl;
}

bool Student::isValidFn(unsigned fn)
{
    size_t cnt = 0;
    while (fn != 0)
    {
        fn /= 10;
        cnt++;
    }
    if (cnt != 5)
    {
        return false;
    }
    return true;
}
