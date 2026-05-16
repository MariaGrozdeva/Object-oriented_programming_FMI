#pragma once
#include "../Person/Person.h"

class Teacher : public Person
{
private:
    char** subjects;
    unsigned int subjectCount;
    unsigned int subjectCapacity;

    void copyFrom(const Teacher& other);
    void free();
    void resize();

public:
    Teacher(const char* name, unsigned int age, const char** subjects, unsigned int subjectCount);
    Teacher();

    Teacher(const Teacher& other);
    Teacher& operator=(const Teacher& other);
    Teacher(Teacher&& other) noexcept;
    Teacher& operator=(Teacher&& other) noexcept;
    ~Teacher();

    void addSubject(const char* subject);
    const char* getSubject(unsigned int index) const;
    unsigned int getSubjectCount() const;
    void print() const;
};
