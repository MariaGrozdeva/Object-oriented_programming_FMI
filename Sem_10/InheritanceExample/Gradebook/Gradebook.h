#pragma once
class Gradebook
{
public:
	Gradebook() = default;
	Gradebook(const Gradebook& other);
	Gradebook& operator=(const Gradebook& other);
	Gradebook(Gradebook&& other) noexcept;
	Gradebook& operator=(Gradebook&& other) noexcept;
	~Gradebook();

	unsigned operator[](unsigned index) const;
	unsigned& operator[](unsigned index);

	const unsigned* getGrades() const;
	unsigned getGradesCnt() const;
	unsigned getCapacity() const;

	void pushGrade(unsigned newGrade);
	void popGrade();
	void removeGrade(unsigned index);

	void print() const;
	
private:
	unsigned* grades;
	unsigned count;
	unsigned capacity;

	void resize(unsigned newCapacity);
	void copyFrom(const Gradebook& other);
	void moveFrom(Gradebook&& other);
	void free();
};

