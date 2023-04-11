#pragma once

class Student
{
private:
	char* name = nullptr;
	unsigned int* grades = nullptr;
	size_t gradesCount = 0;

	void copyName(const char* otherName);
	void copyGrades(const unsigned int* otherGrades, size_t otherGradesCount);

	void copyFrom(const Student& other);
	void free();

public:
	Student(const char* name, const unsigned int* grades, size_t gradesCount);

	Student() = default;
	Student(const Student& other);
	Student& operator=(const Student& other);
	~Student();

	void setName(const char* name);
	void setGrades(const unsigned int* grades, size_t gradesCount);

	const char* getName() const;
	const unsigned int* getGrades() const;
	const size_t getGradesCount() const;
};