#include "Teacher.h"

Teacher::Teacher(const char* name, unsigned age, const char* const* subjects, size_t count) : Person(name, age), subjects(nullptr), count(0)
{
	setSubjects(subjects, count);
}

Teacher::Teacher(const Teacher& other) : Person(other), subjects(nullptr), count(0)
{
	copyFrom(other);
}

Teacher::Teacher(Teacher&& other) noexcept : Person(std::move(other))
{
	moveFrom(std::move(other));
}

Teacher& Teacher::operator=(const Teacher& other)
{
	if (this == &other)
	{
		return *this;
	}
	char** temp = new char* [other.count] {nullptr};
	for (size_t i = 0; i < other.count; i++)
	{
		temp[i] = new (std::nothrow) char[strlen(other.subjects[i]) + 1];
		if (temp[i] == nullptr)
		{
			for (size_t i = 0; i < other.count; i++)
			{
				delete[] temp[i];
			}
			delete[] temp;
			throw std::bad_alloc();
		}
		strcpy(temp[i], other.subjects[i]);
	}
	Person::operator=(other);

	free();
	this->subjects = temp;
	this->count = other.count;

	return *this;
}

Teacher& Teacher::operator=(Teacher&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}
	Person::operator=(std::move(other));
	free();
	moveFrom(std::move(other));
	return *this;
}

Teacher::~Teacher()
{
	free();
}

void Teacher::setSubjects(const char* const* subjects, size_t count)
{
	char** temp = new char* [count] {nullptr};
	for (size_t i = 0; i < count; i++)
	{
		temp[i] = new (std::nothrow) char[strlen(subjects[i]) + 1];
		if (temp[i] == nullptr)
		{
			for (size_t i = 0; i < count; i++)
			{
				delete[] temp[i];
			}
			delete[] temp;
			throw std::bad_alloc();
		}
		strcpy(temp[i], subjects[i]);
	}
	free();
	this->subjects = temp;
	this->count = count;
}

void Teacher::print() const
{
	std::cout << getName() << " " << getAge() << std::endl;
	for (size_t i = 0; i < count; i++)
	{
		std::cout << subjects[i] << std::endl;
	}
}

void Teacher::free()
{
	if (subjects != nullptr)
	{
		for (size_t i = 0; i < count; i++)
		{
			delete[] subjects[i];
		}
	}
	delete[] subjects;
	subjects = nullptr;
	count = 0;
}

void Teacher::copyFrom(const Teacher& other)
{
	subjects = new char* [other.count] {nullptr};
	for (size_t i = 0; i < other.count; i++)
	{
		subjects[i] = new(std::nothrow) char[strlen(other.subjects[i]) + 1];
		if (subjects[i] == nullptr)
		{
			free();
			throw std::bad_alloc();
		}
		strcpy(subjects[i], other.subjects[i]);
	}
	count = other.count;
}

void Teacher::moveFrom(Teacher&& other)
{
	subjects = other.subjects;
	count = other.count;

	other.subjects = nullptr;
	other.count = 0;
}
