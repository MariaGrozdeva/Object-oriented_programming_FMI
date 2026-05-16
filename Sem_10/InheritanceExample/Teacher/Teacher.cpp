#include "Teacher.h"
#include <cstring>
#pragma warning(disable : 4996)

void Teacher::copyFrom(const Teacher& other)
{
    subjectCount = other.subjectCount;
    subjectCapacity = other.subjectCapacity;
    subjects = new char*[subjectCapacity];
    for (unsigned int i = 0; i < subjectCount; i++)
    {
        subjects[i] = new char[strlen(other.subjects[i]) + 1];
        strcpy(subjects[i], other.subjects[i]);
    }
}

void Teacher::free()
{
    for (unsigned int i = 0; i < subjectCount; i++)
    {
        delete[] subjects[i];
    }
    delete[] subjects;
    subjects = nullptr;
    subjectCount = 0;
    subjectCapacity = 0;
}

void Teacher::resize()
{
    subjectCapacity *= 2;
    char** newSubjects = new char*[subjectCapacity];
    for (unsigned int i = 0; i < subjectCount; i++)
    {
        newSubjects[i] = subjects[i];
    }
    delete[] subjects;
    subjects = newSubjects;
}

Teacher::Teacher(const char* name, unsigned int age, const char** subjects, unsigned int subjectCount)
    : Person(name, age), subjectCount(subjectCount), subjectCapacity(subjectCount * 2)
{
    this->subjects = new char*[subjectCapacity];
    for (unsigned int i = 0; i < subjectCount; i++)
    {
        this->subjects[i] = new char[strlen(subjects[i]) + 1];
        strcpy(this->subjects[i], subjects[i]);
    }
}

Teacher::Teacher()
    : Person(), subjects(new char*[2]), subjectCount(0), subjectCapacity(2) {}

Teacher::Teacher(const Teacher& other) : Person(other)
{
    copyFrom(other);
}

Teacher& Teacher::operator=(const Teacher& other)
{
    if (this != &other)
    {
        Person::operator=(other);
        free();
        copyFrom(other);
    }
    return *this;
}

Teacher::Teacher(Teacher&& other) noexcept
    : Person(std::move(other)), subjects(other.subjects),
      subjectCount(other.subjectCount), subjectCapacity(other.subjectCapacity)
{
    other.subjects = nullptr;
    other.subjectCount = 0;
    other.subjectCapacity = 0;
}

Teacher& Teacher::operator=(Teacher&& other) noexcept
{
    if (this != &other)
    {
        Person::operator=(std::move(other));
        free();
        subjects = other.subjects;
        subjectCount = other.subjectCount;
        subjectCapacity = other.subjectCapacity;
        other.subjects = nullptr;
        other.subjectCount = 0;
        other.subjectCapacity = 0;
    }
    return *this;
}

Teacher::~Teacher()
{
    free();
}

void Teacher::addSubject(const char* subject)
{
    if (subjectCount == subjectCapacity)
    {
        resize();
    }
    subjects[subjectCount] = new char[strlen(subject) + 1];
    strcpy(subjects[subjectCount], subject);
    subjectCount++;
}

const char* Teacher::getSubject(unsigned int index) const
{
    if (index >= subjectCount)
    {
        return nullptr;
    }
    return subjects[index];
}

unsigned int Teacher::getSubjectCount() const
{
    return subjectCount;
}

void Teacher::print() const
{
    Person::print();
    std::cout << "Subjects (" << subjectCount << "):" << std::endl;
    for (unsigned int i = 0; i < subjectCount; i++)
    {
        std::cout << "  - " << subjects[i] << std::endl;
    }
}
