#include "Student.h"
#include <cstring>
#pragma warning (disable : 4996)

Student::Student(const char* name, const unsigned int* grades, size_t gradesCount)
{
    setName(name);
    setGrades(grades, gradesCount);
}
Student::Student(const Student& other)
{
    copyFrom(other);
}
Student& Student::operator=(const Student& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
Student::~Student()
{
    free();
}

void Student::setName(const char* name)
{
    if (name == nullptr || this->name == name)
    {
        return;
    }
    delete[] this->name;
    copyName(name);
}
void Student::setGrades(const unsigned int* grades, size_t gradesCount)
{
    if (grades == nullptr || this->grades == grades)
    {
        return;
    }
    delete[] this->grades;
    copyGrades(grades, gradesCount);
}

const char* Student::getName() const
{
    return name;
}
const unsigned int* Student::getGrades() const
{
    return grades;
}
const size_t Student::getGradesCount() const
{
    return gradesCount;
}

void Student::copyName(const char* otherName)
{
    name = new char[strlen(otherName) + 1];
    strcpy(name, otherName);
}
void Student::copyGrades(const unsigned int* otherGrades, size_t otherGradesCount)
{
    gradesCount = otherGradesCount;
    grades = new unsigned int[gradesCount];
    for (size_t i = 0; i < gradesCount; i++)
    {
        grades[i] = otherGrades[i];
    }
}

void Student::copyFrom(const Student& other)
{
    copyName(other.name);
    copyGrades(other.grades, other.gradesCount);
}
void Student::free()
{
    delete[] name, grades;
    name = nullptr;
    grades = nullptr;
    gradesCount = 0;
}