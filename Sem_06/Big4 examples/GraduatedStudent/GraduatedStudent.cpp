#include "GraduatedStudent.h"
#include <cstring>

#pragma warning (disable : 4996)

double GraduatedStudent::m_averageGradeForAllGraduates = 0;
size_t GraduatedStudent::m_allGraduatesCount = 0;

GraduatedStudent::GraduatedStudent(const char* name, const unsigned* grades, size_t gradesCount, const char* quote)
{
	setName(name);
	setGrades(grades, gradesCount);
	setQuote(quote);
}

GraduatedStudent::GraduatedStudent(const GraduatedStudent& other)
{
	copyFrom(other);
}

GraduatedStudent& GraduatedStudent::operator=(const GraduatedStudent& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

GraduatedStudent::~GraduatedStudent()
{
	free();
}

void GraduatedStudent::setName(const char* newName)
{
	if (!newName || newName == m_name)
	{
		return;
	}
	
	delete[] m_name;
	m_name = new char[strlen(newName) + 1];
	strcpy(m_name, newName);
}

void GraduatedStudent::setGrades(const unsigned* newGrades, size_t newGradesCount)
{
	if (!newGrades || m_grades == newGrades)
	{
		return;
	}

	delete[] m_grades;
	m_grades = new unsigned[newGradesCount];
	m_gradesCount = newGradesCount;
	for (size_t i = 0; i < newGradesCount; i++)
	{
		m_grades[i] = newGrades[i];
	}
	
	m_averageGradeForAllGraduates *= m_allGraduatesCount;
	m_averageGradeForAllGraduates -= m_averageGrade;
    	if (m_averageGrade == 0) // it is 0 only when the current object is a newly added student (all others have some positive average grades)
    	{
        	m_allGraduatesCount++;
    	}
	updateAverageGrade();
	(m_averageGradeForAllGraduates += m_averageGrade) /= m_allGraduatesCount;
}

void GraduatedStudent::setQuote(const char* newQuote)
{
	if (!newQuote || strlen(newQuote) > m_maxQuoteSize)
	{
		return;
	}
	
	strcpy(m_quote, newQuote);
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
    	unsigned gradesSum = 0;
    	for (size_t i = 0; i < m_gradesCount; i++)
    	{
        	gradesSum += m_grades[i];
    	}
    	m_averageGrade = static_cast<double>(gradesSum) / m_gradesCount;
}

void GraduatedStudent::copyFrom(const GraduatedStudent& other)
{
	m_name = new char[strlen(other.m_name) + 1];
	strcpy(m_name, other.m_name);

	m_grades = new unsigned[other.m_gradesCount];
	for (size_t i = 0; i < other.m_gradesCount; i++)
	{
		m_grades[i] = other.m_grades[i];
	}
	m_gradesCount = other.m_gradesCount;
	m_averageGrade = other.m_averageGrade;

	strcpy(m_quote, other.m_quote);
	
	m_averageGradeForAllGraduates *= m_allGraduatesCount;
	m_allGraduatesCount++;
	(m_averageGradeForAllGraduates += m_averageGrade) /= m_allGraduatesCount;
}

void GraduatedStudent::free()
{
    	m_averageGradeForAllGraduates *= m_allGraduatesCount;
	if (--m_allGraduatesCount)
	{
		(m_averageGradeForAllGraduates -= m_averageGrade) /= m_allGraduatesCount;
	}
	else
	{
		m_averageGradeForAllGraduates = 0;
	}
	
	delete[] m_name;
	delete[] m_grades;

	m_name = nullptr;
	m_grades = nullptr;
	m_gradesCount = 0;
	m_averageGrade = 0;
	strcpy(m_quote, "");
}
