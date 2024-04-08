#pragma once
#include <iostream>

class GraduatedStudent
{
public:
    	GraduatedStudent(const char* name, const unsigned* grades, size_t gradesCount, const char* quote);

	GraduatedStudent() = default;
	GraduatedStudent(const GraduatedStudent& other);
	GraduatedStudent& operator=(const GraduatedStudent& other);
	~GraduatedStudent();

	void setName(const char* newName);
	void setGrades(const unsigned* newGrades, size_t newGradesCount);
	void setQuote(const char* quote);

	const char* name() const;
	const unsigned* grades() const;
	size_t gradesCount() const;
	double averageGrade() const;
	const char* quote() const;
	
	static double averageGradeForAllGraduates();
	static size_t allGraduatesCount();
	
private:
	char* m_name = nullptr;
	unsigned* m_grades = nullptr;
	size_t m_gradesCount = 0;
	double m_averageGrade = 0;
	
	static constexpr size_t m_maxQuoteSize = 32;
	char m_quote[m_maxQuoteSize + 1] = "";
	
	static double m_averageGradeForAllGraduates;
	static size_t m_allGraduatesCount;
	
	void updateAverageGrade();
	
	void copyFrom(const GraduatedStudent& other);
	void free();
};
