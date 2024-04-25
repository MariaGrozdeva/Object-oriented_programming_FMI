#include "Teacher.h"
#include <exception>
#include <iostream>
#pragma warning (disable : 4996)

Teacher::Teacher() : subjects(nullptr), subCount(0), subCapacity(0)
{
	subjects = new char* [2] {nullptr};
	subCapacity = 2;
}

Teacher::Teacher(const char* name, unsigned age, const char* const* subjects, size_t subCount) : Person(name, age), subjects(nullptr), subCount(0), subCapacity(0)
{
	setSubjects(subjects, subCount);
}

Teacher::Teacher(const Teacher& other) : Person(other), subjects(nullptr), subCount(0), subCapacity(0)
{
	setSubjects(other.subjects, other.subCount);
}

Teacher::Teacher(Teacher&& other) noexcept : Person(std::move(other))
{
	subjects = other.subjects;
	subCount = other.subCount;
	subCapacity = other.subCapacity;
	other.subjects = nullptr;
	other.subCount = 0;
	other.subCapacity = 0;
}

Teacher& Teacher::operator=(const Teacher& other)
{
	if (this == &other)
		return *this;

	char** tempSubs = new char* [other.subCapacity] {nullptr};
	for (size_t i = 0; i < other.subCount; ++i)
	{
		tempSubs[i] = new (std::nothrow) char[strlen(other.subjects[i]) + 1];
		if (!tempSubs[i])
		{
			for (size_t j = 0; j < i; ++j)
			{
				delete[] tempSubs[j];
			}
			delete[] tempSubs;
			throw std::bad_alloc();
		}
		strcpy(tempSubs[i], other.subjects[i]);
	}

	try
	{
		Person::operator=(other);
	}
	catch (...)
	{
		for (size_t i = 0; i < other.subCount; ++i)
		{
			delete[] tempSubs[i];
		}
		delete[] tempSubs;

		throw;
	}

	free();
	subjects = tempSubs;
	subCount = other.subCount;
	subCapacity = other.subCapacity;

	return *this;
}

Teacher& Teacher::operator=(Teacher&& other) noexcept
{
	if (this == &other)
		return *this;

	Person::operator=(std::move(other));
	free();
	subjects = other.subjects;
	subCount = other.subCount;
	subCapacity = other.subCapacity;
	other.subjects = nullptr;
	other.subCount = 0;
	other.subCapacity = 0;

	return *this;
}

Teacher::~Teacher()
{
	free();
}

void Teacher::addSubject(const char* sub)
{
	resize();
	subjects[subCount] = new char[strlen(sub) + 1];
	strcpy(subjects[subCount], sub);
	++subCount;
}

void Teacher::removeSubject(const char* sub)
{
	for (int i = 0; i < subCount; i++)
	{
		if (strcmp(subjects[i], sub) == 0)
		{
			delete[] subjects[i];
			for (int j = i+1; j < subCount; j++)
			{
				subjects[j - 1] = subjects[j];
			}
			subjects[subCount - 1] = nullptr;
			--subCount;
			--i;
		}
	}
	resize();
}

void Teacher::setSubjects(const char* const* subs, size_t count)
{
	char** tempSubs = new char* [count] {nullptr};
	for (size_t i = 0; i < count; ++i)
	{
		tempSubs[i] = new (std::nothrow) char[strlen(subs[i]) + 1];
		if (!tempSubs[i])
		{
			for (size_t j = 0; j < i; ++j)
			{
				delete[] tempSubs[j];
			}
			delete[] tempSubs;
			throw std::bad_alloc();
		}
		strcpy(tempSubs[i], subs[i]);
	}

	free();
	subjects = tempSubs;
	subCount = count;
	subCapacity = count;
}

void Teacher::free()
{
	if (subjects)
		for (size_t i = 0; i < subCount; ++i)
		{
			delete[] subjects[i];
		}
	delete[] subjects;
	subCount = subCapacity = 0;
}

void Teacher::resize()
{
	if (subCount >= subCapacity)
	{
		char** tempSubs = new char* [subCapacity*2] {nullptr};
		for (size_t i = 0; i < subCount; ++i)
		{
			tempSubs[i] = new (std::nothrow) char[strlen(subjects[i]) + 1];
			if (!tempSubs[i])
			{
				for (size_t j = 0; j < i; ++j)
				{
					delete[] tempSubs[j];
				}
				delete[] tempSubs;
				throw std::bad_alloc();
			}
			strcpy(tempSubs[i], subjects[i]);
		}

		if (subjects)
			for (size_t i = 0; i < subCount; ++i)
			{
				delete[] subjects[i];
			}
		delete[] subjects;
		subjects = tempSubs;
		subCapacity *= 2;
	}

	if (subCount != 0 && subCount <= subCapacity / 4)
	{
		char** tempSubs = new char* [subCapacity / 4] {nullptr};
		for (size_t i = 0; i < subCount; ++i)
		{
			tempSubs[i] = new (std::nothrow) char[strlen(subjects[i]) + 1];
			if (!tempSubs[i])
			{
				for (size_t j = 0; j < i; ++j)
				{
					delete[] tempSubs[j];
				}
				delete[] tempSubs;
				throw std::bad_alloc();
			}
			strcpy(tempSubs[i], subjects[i]);
		}

		if (subjects)
			for (size_t i = 0; i < subCount; ++i)
			{
				delete[] subjects[i];
			}
		delete[] subjects;
		subjects = tempSubs;
		subCapacity /= 4;
	}
}
