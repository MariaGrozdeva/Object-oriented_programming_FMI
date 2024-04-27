#include "Gradebook.h"
#include <iostream>

void Gradebook::resize(unsigned newCapacity)
{
	unsigned* temp = new unsigned[newCapacity];
	for (size_t i = 0; i < count; i++)
	{
		temp[i] = grades[i];
	}
	delete[] grades;
	grades = temp;

	capacity = newCapacity;
}

void Gradebook::copyFrom(const Gradebook& other)
{
	try
	{
		unsigned* temp = new unsigned[other.capacity];
		for (size_t i = 0; i < other.count; i++)
		{
			temp[i] = other.grades[i];
		}
		delete[] grades;
		grades = temp;

		count = other.count;
		capacity = other.capacity;
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "Bad alloc occured Gradebook::copyFrom. Object remains unchaged/ will not be created\n";
		throw e;
	}
}

void Gradebook::moveFrom(Gradebook&& other)
{
	grades = other.grades;
	count = other.count;
	capacity = other.capacity;

	other.grades = nullptr;
	other.count = 0;
	other.capacity = 0;
}

void Gradebook::free()
{
	delete[] grades;
	count = 0;
	capacity = 0;
}

Gradebook::Gradebook(const Gradebook& other)
{
	copyFrom(other);
}

Gradebook& Gradebook::operator=(const Gradebook& other) 
{
	if (this != &other)
		copyFrom(other); // delete[] grades is performed in copyFrom to ensure strong exception safety

	return *this;
}

Gradebook::Gradebook(Gradebook&& other) noexcept
{
	moveFrom(std::move(other));
}

Gradebook& Gradebook::operator=(Gradebook&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Gradebook::~Gradebook()
{
	free();
}

unsigned Gradebook::operator[](unsigned index) const
{
	return grades[index];
}

unsigned& Gradebook::operator[](unsigned index)
{
	return grades[index];
}

const unsigned* Gradebook::getGrades() const
{
	return grades;
}

unsigned Gradebook::getGradesCnt() const
{
	return count;
}

unsigned Gradebook::getCapacity() const
{
	return capacity;
}

void Gradebook::pushGrade(unsigned newGrade)
{	
	if (newGrade < 2 || newGrade > 6)
		throw std::invalid_argument("Grade was out of domain[2,6]");

	if (capacity == 0)
		resize(1);

	else if (count == capacity)
		resize(2 * capacity);

	grades[count++] = newGrade;
}

void Gradebook::popGrade()
{
	if (count == capacity / 4)
		resize(capacity / 2);

	count--;
}

void Gradebook::removeGrade(unsigned index)
{
	if (index >= count)
		throw std::invalid_argument("Index was out of bounds");

	if (count == capacity / 4)
		resize(capacity / 2);

	for (size_t i = index; i < count - 1; i++)
	{
		grades[i] = grades[i + 1];
	}

	count--;
}

void Gradebook::print() const
{
	std::cout << "Grades: ";
	for (size_t i = 0; i < count; i++)
	{
		std::cout << grades[i] << ' ';
	}
	std::cout << std::endl;
}
