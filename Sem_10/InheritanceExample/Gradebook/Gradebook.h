#pragma once
class Gradebook
{
public:
	Gradebook();
	Gradebook(const Gradebook& other);
	Gradebook& operator=(const Gradebook& other);
	~Gradebook();

	void add(unsigned newGrade);
	void remove(unsigned index);
	void popBack();

	unsigned& operator[](unsigned index);
	unsigned operator[](unsigned index) const;

	double getAverage() const;
	unsigned getCount() const;
	unsigned getCapacity() const;

private:	
	unsigned* grades;
	unsigned count;
	unsigned capacity;

	double average;

	void copyFrom(const Gradebook& other);
	void free();

	void resize(unsigned newSize);
};

