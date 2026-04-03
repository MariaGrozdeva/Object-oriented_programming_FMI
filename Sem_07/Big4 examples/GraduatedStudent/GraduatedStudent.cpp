#include "GraduatedStudent.h"
#include <cstring>
#include <stdexcept>
#include <new> // std::bad_alloc

#pragma warning(disable : 4996)

double GraduatedStudent::m_averageGradeForAllGraduates = 0;
size_t GraduatedStudent::m_allGraduatesCount = 0;

GraduatedStudent::GraduatedStudent(const char* name, const unsigned* grades, size_t gradesCount, const char* quote)
    : m_name(nullptr), m_grades(nullptr), m_gradesCount(0), m_averageGrade(0)
{
    m_quote[0] = '\0';

    if (!name || !grades || gradesCount == 0 || !quote || std::strlen(quote) > m_maxQuoteSize)
    {
        throw std::invalid_argument("Invalid student data");
    }

    m_name = new char[std::strlen(name) + 1];
    std::strcpy(m_name, name);

    try
    {
        m_grades = new unsigned[gradesCount];
    }
    catch (const std::bad_alloc&)
    {
        delete[] m_name;
        m_name = nullptr;
        throw;
    }
    for (size_t i = 0; i < gradesCount; i++)
    {
        m_grades[i] = grades[i];
    }

    m_gradesCount = gradesCount;
    std::strcpy(m_quote, quote);

    updateAverageGrade();
    registerStudent();
}

GraduatedStudent::GraduatedStudent(const GraduatedStudent& other)
    : m_name(nullptr), m_grades(nullptr), m_gradesCount(0), m_averageGrade(0)
{
    m_quote[0] = '\0';

    m_name = new char[std::strlen(other.m_name) + 1];
    std::strcpy(m_name, other.m_name);

    try
    {
        m_grades = new unsigned[other.m_gradesCount];
    }
    catch (const std::bad_alloc&)
    {
        delete[] m_name;
        m_name = nullptr;
        throw;
    }
    for (size_t i = 0; i < other.m_gradesCount; i++)
    {
        m_grades[i] = other.m_grades[i];
    }
	
    m_gradesCount = other.m_gradesCount;
    m_averageGrade = other.m_averageGrade;
    std::strcpy(m_quote, other.m_quote);

    registerStudent();
}

GraduatedStudent& GraduatedStudent::operator=(const GraduatedStudent& other)
{
    if (this != &other)
    {
        char* newName = new char[std::strlen(other.m_name) + 1];
        unsigned* newGrades = nullptr;
        try
        {
            newGrades = new unsigned[other.m_gradesCount];
        }
        catch (const std::bad_alloc&)
        {
            delete[] newName;
            throw;
        }

        std::strcpy(newName, other.m_name);
        for (size_t i = 0; i < other.m_gradesCount; i++)
        {
            newGrades[i] = other.m_grades[i];
        }

        unregisterStudent();

        delete[] m_name;
        delete[] m_grades;

        m_name = newName;
        m_grades = newGrades;
        m_gradesCount = other.m_gradesCount;
        m_averageGrade = other.m_averageGrade;
        std::strcpy(m_quote, other.m_quote);

        registerStudent();
    }
    return *this;
}

GraduatedStudent::~GraduatedStudent()
{
    unregisterStudent();
    delete[] m_name;
    delete[] m_grades;
}

void GraduatedStudent::setName(const char* newName)
{
    if (!newName)
    {
        return;
    }

    char* temp = new char[std::strlen(newName) + 1];
    std::strcpy(temp, newName);

    delete[] m_name;
    m_name = temp;
}

void GraduatedStudent::setGrades(const unsigned* newGrades, size_t newGradesCount)
{
    if (!newGrades || newGradesCount == 0)
    {
        return;
    }

    unsigned* temp = new unsigned[newGradesCount];
    for (size_t i = 0; i < newGradesCount; i++)
    {
        temp[i] = newGrades[i];
    }

    unregisterStudent();

    delete[] m_grades;
    m_grades = temp;
    m_gradesCount = newGradesCount;

    updateAverageGrade();
    registerStudent();
}

void GraduatedStudent::setQuote(const char* newQuote)
{
    if (!newQuote || std::strlen(newQuote) > m_maxQuoteSize)
    {
        return;
    }

    std::strcpy(m_quote, newQuote);
}

const char* GraduatedStudent::name() const
{
    return m_name;
}

const unsigned* GraduatedStudent::grades() const
{
    return m_grades;
}

size_t GraduatedStudent::gradesCount() const
{
    return m_gradesCount;
}

double GraduatedStudent::averageGrade() const
{
    return m_averageGrade;
}

const char* GraduatedStudent::quote() const
{
    return m_quote;
}

double GraduatedStudent::averageGradeForAllGraduates()
{
    return m_averageGradeForAllGraduates;
}

size_t GraduatedStudent::allGraduatesCount()
{
    return m_allGraduatesCount;
}

void GraduatedStudent::updateAverageGrade()
{
    unsigned sum = 0;
    for (size_t i = 0; i < m_gradesCount; i++)
    {
        sum += m_grades[i];
    }

    m_averageGrade = static_cast<double>(sum) / m_gradesCount;
}

void GraduatedStudent::registerStudent()
{
    m_averageGradeForAllGraduates *= m_allGraduatesCount;
    m_averageGradeForAllGraduates += m_averageGrade;
    m_allGraduatesCount++;
    m_averageGradeForAllGraduates /= m_allGraduatesCount;
}

void GraduatedStudent::unregisterStudent()
{
    if (m_allGraduatesCount == 0)
    {
        return;
    }

    m_averageGradeForAllGraduates *= m_allGraduatesCount;
    m_averageGradeForAllGraduates -= m_averageGrade;
    m_allGraduatesCount--;

    if (m_allGraduatesCount == 0)
    {
        m_averageGradeForAllGraduates = 0;
    }
    else
    {
        m_averageGradeForAllGraduates /= m_allGraduatesCount;
    }
}
