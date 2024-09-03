#pragma warning(disable : 4996)
#include "Teacher.h"
#include <cstring>
#include <iostream>

void Teacher::free()
{
	if (!subjects)
		return;

	for (size_t i = 0; i < subjectsCount; i++)
	{
		delete[] subjects[i];
	}

	delete[] subjects;
}

void Teacher::copyFrom(const Teacher& other)
{
	char** temp = new char* [other.capacity] {nullptr};
	try
	{		
		for (size_t i = 0; i < other.subjectsCount; i++)
		{
			temp[i] = new char[strlen(other.subjects[i]) + 1];
			strcpy(temp[i], other.subjects[i]);
		}

		delete[] subjects;
		subjects = temp;
		subjectsCount = other.subjectsCount;
		capacity = other.capacity;
	}
	catch (const std::bad_alloc& e)
	{
		for (size_t i = 0; temp[i]; i++)
		{
			delete[] temp[i];
		}

		delete[] temp;
		throw e;
	}
}

void Teacher::moveFrom(Teacher&& other)
{
	subjects = other.subjects;
	subjectsCount = other.subjectsCount;
	capacity = other.capacity;

	other.subjects = nullptr;
	other.subjectsCount = 0;
	other.capacity = 0;
}

void Teacher::resize(unsigned newCapacity)
{
	char** temp = new char* [newCapacity] {nullptr};
	for (size_t i = 0; i < subjectsCount; i++)
	{
		temp[i] = subjects[i];
	}

	delete[] subjects;
	subjects = temp;
	capacity = newCapacity;
}

Teacher::Teacher(const char* name, unsigned age, const char* const* subjects, unsigned subjectsCount)
	: Person(name, age), subjects(nullptr), subjectsCount(0)
{
	setSubjects(subjects, subjectsCount);	
	capacity = subjectsCount;
}

Teacher::Teacher(const Teacher& other)
{
	copyFrom(other);
}

Teacher& Teacher::operator=(const Teacher& other)
{
	Person:: operator=(other);
	if (this != &other)
	{
		copyFrom(other);
	}

	return *this;
}

Teacher::Teacher(Teacher&& other) noexcept
	:Person(std::move(other))
{
	moveFrom(std::move(other));
}

Teacher& Teacher::operator=(Teacher&& other) noexcept
{	
	Person::operator=(std::move(other));
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
	subjectsCount = 0;
	capacity = 0;
}

const char* const* Teacher::getSubjects() const
{
	return subjects;
}

unsigned Teacher::getSubjectsCount() const
{
	return subjectsCount;
}

void Teacher::setSubjects(const char* const* subjects, unsigned subjectsCount)
{
	char** temp = new char* [subjectsCount] {nullptr};
	try
	{
		for (size_t i = 0; i < subjectsCount; i++)
		{
			temp[i] = new char[strlen(subjects[i]) + 1];
			strcpy(temp[i], subjects[i]);
		}		

		free();
		this->subjects = temp;
		this->subjectsCount = subjectsCount;
	}
	catch (const std::bad_alloc& e)
	{
		for (size_t i = 0; temp[i]; i++)
		{
			delete[] temp[i];
		}
		delete[] temp;
		throw e;
	}
}

void Teacher::addSubject(const char* subject)
{
	if (subjectsCount == capacity)
		resize(capacity * 2);

	subjects[subjectsCount] = new char[strlen(subject) + 1];
	strcpy(subjects[subjectsCount++], subject);
}

void Teacher::removeSubjectAt(unsigned index)
{
	if (index >= subjectsCount)
		throw std::invalid_argument("Invalid index");

	delete[] subjects[index];
	for (size_t i = 0; i < subjectsCount - 1; i++)
	{
		subjects[i] = subjects[i + 1];
	}
	subjects[subjectsCount--] = nullptr;

	if (subjectsCount <= capacity / 4)
		resize(capacity / 2);
}

void Teacher::removeSubject()
{
	if (subjectsCount == 0)
		return;

	delete[] subjects[subjectsCount - 1];
	subjectsCount -= 1;
	subjects[subjectsCount] = nullptr;
	
	if (subjectsCount <= capacity / 4)
		resize(capacity / 2);
}
