#include "GraduatedStudent.h"

#include <cstring>
#include <new>
#include <stdexcept>

GraduatedStudent::GraduatedStudent(
    const char *name,
    const unsigned *grades,
    const std::size_t gradesCount,
    const char *quote
)
{
    if (!name ||
        !grades || gradesCount == 0 ||
        !quote ||
        std::strlen(quote) > MAX_QUOTE_LEN)
    {
        throw std::invalid_argument("Invalid student data");
    }

    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);

    try
    {
        this->grades = new unsigned[gradesCount];
    } catch (const std::bad_alloc &)
    {
        delete[] this->name;
        this->name = nullptr;
        throw;
    }
    std::strcpy(this->quote, quote);

    for (std::size_t i = 0; i < gradesCount; i++)
    {
        this->grades[i] = grades[i];
    }

    this->gradesCount = gradesCount;
    updateAverageGrade();
    addToClassData();
}

GraduatedStudent::GraduatedStudent(const GraduatedStudent &other)
{
    char *tempName = nullptr;
    unsigned *tempGrades = nullptr;
    try
    {
        tempName = new char[std::strlen(other.name) + 1];
        std::strcpy(tempName, other.name);
        tempGrades = new unsigned[other.gradesCount];
    } catch (const std::bad_alloc &)
    {
        delete[] tempGrades;
        delete[] tempName;
        throw;
    }
    for (std::size_t i = 0; i < other.gradesCount; i++)
    {
        tempGrades[i] = other.grades[i];
    }
    name = tempName;
    grades = tempGrades;
    gradesCount = other.gradesCount;
    std::strcpy(quote, other.quote);
    averageGrade = other.averageGrade;
    addToClassData();
}

GraduatedStudent &GraduatedStudent::operator=(const GraduatedStudent &other)
{
    if (this == &other)
    {
        return *this;
    }
    char *tempName = nullptr;
    unsigned *tempGrades = nullptr;
    try
    {
        tempName = new char[std::strlen(other.name) + 1];
        std::strcpy(tempName, other.name);
        tempGrades = new unsigned[other.gradesCount];
    } catch (const std::bad_alloc &)
    {
        delete[] tempGrades;
        delete[] tempName;
        throw;
    }
    for (std::size_t i = 0; i < other.gradesCount; i++)
    {
        tempGrades[i] = other.grades[i];
    }
    delete[] grades;
    delete[] name;
    name = tempName;
    grades = tempGrades;
    gradesCount = other.gradesCount;
    std::strcpy(quote, other.quote);
    const double oldAverageGrade = averageGrade;
    averageGrade = other.averageGrade;
    updateToClassData(oldAverageGrade);
    return *this;
}

GraduatedStudent::~GraduatedStudent()
{
    removeFromClassData();
    delete[] name;
    delete[] grades;
}

const char *GraduatedStudent::getName() const
{
    return name;
}

const unsigned *GraduatedStudent::getGrades() const
{
    return grades;
}

std::size_t GraduatedStudent::getGradesCount() const
{
    return gradesCount;
}

double GraduatedStudent::getAverageGrade() const
{
    return averageGrade;
}

const char *GraduatedStudent::getQuote() const
{
    return quote;
}

void GraduatedStudent::setName(const char *newName)
{
    if (!newName)
    {
        throw std::invalid_argument("Invalid student name");
    }
    char *temp = new char[std::strlen(newName) + 1];
    std::strcpy(temp, newName);

    delete[] name;
    name = temp;
}

void GraduatedStudent::setGrades(
    const unsigned *newGrades,
    const std::size_t newGradesCount
)
{
    if (!newGrades || newGradesCount == 0)
    {
        throw std::invalid_argument("Invalid student grades");
    }
    unsigned *temp = new unsigned[newGradesCount];
    const double oldAverageGrade = averageGrade;
    for (std::size_t i = 0; i < newGradesCount; i++)
    {
        temp[i] = newGrades[i];
    }
    delete[] grades;
    grades = temp;
    gradesCount = newGradesCount;
    updateAverageGrade();
    updateToClassData(oldAverageGrade);
}

void GraduatedStudent::setQuote(const char *newQuote)
{
    if (!newQuote || std::strlen(newQuote) > MAX_QUOTE_LEN)
    {
        throw std::invalid_argument("Invalid student quote");
    }
    std::strcpy(quote, newQuote);
}

double GraduatedStudent::getAverageGradeForAllGraduates()
{
    if (graduatedStudentsCount == 0)
    {
        return 0.0;
    }
    return averageGradeSumAllGraduates / graduatedStudentsCount;
}

std::size_t GraduatedStudent::getGraduatedStudentsCount()
{
    return graduatedStudentsCount;
}

void GraduatedStudent::updateAverageGrade()
{
    unsigned sum = 0;
    for (std::size_t i = 0; i < gradesCount; i++)
    {
        sum += grades[i];
    }
    averageGrade = static_cast<double>(sum) / gradesCount;
}

void GraduatedStudent::addToClassData() const
{
    averageGradeSumAllGraduates += averageGrade;
    graduatedStudentsCount++;
}

void GraduatedStudent::removeFromClassData() const
{
    averageGradeSumAllGraduates -= averageGrade;
    graduatedStudentsCount--;
}

void GraduatedStudent::updateToClassData(const double oldAverageGrade) const
{
    averageGradeSumAllGraduates -= oldAverageGrade;
    averageGradeSumAllGraduates += averageGrade;
}


