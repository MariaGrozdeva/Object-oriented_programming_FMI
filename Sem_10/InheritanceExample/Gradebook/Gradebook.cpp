#include "Gradebook.h"
#include <iostream>

void Gradebook::copyFrom(const Gradebook& other)
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
	average = other.average;
}

void Gradebook::free()
{
	delete[] grades;
	grades = nullptr;
	count = 0;
	capacity = 0;
	average = 0;
}

void Gradebook::resize(unsigned newSize)
{
	unsigned* temp = new unsigned[newSize];
	for (size_t i = 0; i < count; i++)
	{
		temp[i] = grades[i];
	}

	delete[] grades;
	grades = temp;

	capacity = newSize;
}

Gradebook::Gradebook()
	: grades(nullptr), count(0), capacity(0), average(0)
{
}

Gradebook::Gradebook(const Gradebook& other)
{
	copyFrom(other);
}

Gradebook& Gradebook::operator=(const Gradebook& other)
{
	if (this != &other)
		copyFrom(other);

	return *this;
}

Gradebook::~Gradebook()
{
	free();
}

void Gradebook::add(unsigned newGrade)
{
	if (newGrade < 2 || newGrade > 6)
	{
		std::cerr << "Invalid argument for new grade\n";
		return;
	}
		
	if (count == capacity)
		resize(capacity * 2);

	average = average*count + newGrade;
	grades[count++] = newGrade;
	average /= count;
}

void Gradebook::remove(unsigned index)
{
	if (index >= count)
	{
		std::cerr << "Invalid argument for index\n";
		return;
	}

	average = average * count - grades[index];

	for (size_t i = index; i < count - 1; i++)
	{
		grades[i] = grades[i + 1];
	}

	count--;
	average /= count;
	if (count <= capacity / 4)
		resize(capacity / 2);
}

void Gradebook::popBack()
{
	average = average * count - grades[count - 1];
	count--;
	average /= count;
}

unsigned& Gradebook::operator[](unsigned index)
{	
	return grades[index];
}

unsigned Gradebook::operator[](unsigned index) const
{
	return grades[index];
}

double Gradebook::getAverage() const
{
	return average;
}

unsigned Gradebook::getCount() const
{
	return count;
}

unsigned Gradebook::getCapacity() const
{
	return capacity;
}
