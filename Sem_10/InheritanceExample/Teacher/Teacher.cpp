// TODO: insert return statement here
#pragma warning (disable : 4996)
#include "Teacher.h"
#include <cstring>
#include <iostream>

void Teacher::free()
{
	for (size_t i = 0; i < subjectsCount; i++)
	{
		delete[] subjects[i];
	}

	delete[] subjects;
	subjectsCount = 0;
}

void Teacher::copyFrom(const Teacher& other)
{
	subjects = new char* [other.subjectsCount];
	for (size_t i = 0; i < other.subjectsCount; i++)
	{
		subjects[i] = new char[strlen(other.subjects[i]) + 1];
		strcpy(subjects[i], other.subjects[i]);
	}

	subjectsCount = other.subjectsCount;
}

void Teacher::moveFrom(Teacher&& other)
{
	subjects = other.subjects;
	subjectsCount = other.subjectsCount;
	subjectsCapacity = other.subjectsCapacity;

	other.subjects = nullptr;
	other.subjectsCount = 0;
	other.subjectsCapacity = 0;
}

void Teacher::resize(unsigned newSize)
{
	char** temp = new char* [newSize] {nullptr};
	for (size_t i = 0; i < subjectsCount; i++)
	{
		temp[i] = subjects[i];
	}
	
	delete[] subjects;
	subjects = temp;

	subjectsCapacity = newSize;
}

Teacher& Teacher::operator=(const Teacher& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Teacher :: Teacher(Teacher&& other) noexcept
{
	moveFrom(std::move(other));
}

Teacher& Teacher::operator=(Teacher&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Teacher::~Teacher()
{
	free();
}

void Teacher::addSubject(const char* newSubject)
{
	char* temp = new char[strlen(newSubject) + 1];
	strcpy(temp, newSubject);
	if (subjectsCount == subjectsCapacity)
		resize(subjectsCapacity * 2);

	subjects[subjectsCount++] = temp;
}

void Teacher::removeSubject(unsigned index)
{
	if(index >= subjectsCount)
	{
		std::cerr << "Invalid index argument\n";
	}

	delete subjects[index];
	
	for (size_t i = index; i < subjectsCount - 1; i++)
	{
		subjects[i] = subjects[i + 1];
	}

	subjectsCount--;
	if (subjectsCount <= subjectsCapacity / 4)
		resize(subjectsCapacity / 2);
}

unsigned Teacher::getSubjectsCount() const
{
	return subjectsCount;
}

unsigned Teacher::getSubjectsCapacity() const
{
	return subjectsCapacity;
}

char** Teacher::getSubjects() const
{
	return subjects;
}

const char* Teacher::operator[](unsigned index) const
{	
	return subjects[index];
}

char* Teacher::operator[](unsigned index)
{
	return subjects[index];
}
