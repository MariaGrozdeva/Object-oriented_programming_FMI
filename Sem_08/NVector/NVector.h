#pragma once
#include <iostream>

class NVector
{
private:
	int* data;
	size_t size;

	void copyFrom(const NVector& other);
	void free();

public:
	NVector(size_t size);
	NVector(const NVector& other);
	NVector& operator=(const NVector& other);
	~NVector();

	size_t getSize() const;

	NVector& operator+=(const NVector& other);
	NVector& operator-=(const NVector& other);

	NVector& operator*=(size_t scalar);

	int& operator[](size_t index);
	int operator[](size_t index) const;

	friend std::ostream& operator<<(std::ostream& os, const NVector& v);
	friend std::istream& operator>>(std::istream& is, NVector& v);
};

NVector operator+(const NVector& lhs, const NVector& rhs);
NVector operator-(const NVector& lhs, const NVector& rhs);

//So it could be commutative
NVector operator*(const NVector& v, size_t scalar);
NVector operator*(size_t scalar, const NVector& v);

//are parallel
bool operator||(const NVector& lhs, const NVector& rhs);

//are perpendicular
bool operator|=(const NVector& lhs, const NVector& rhs);