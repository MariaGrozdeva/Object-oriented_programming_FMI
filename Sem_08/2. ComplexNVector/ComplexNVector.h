#pragma once
#include <iostream>
#include "ComplexNumber.h"

class ComplexNVector
{
private:
    ComplexNumber* data;
    size_t size;

public:
    ComplexNVector(size_t size);
    ComplexNVector(const ComplexNVector& other);
    ComplexNVector& operator=(const ComplexNVector& other);
    ~ComplexNVector();

    size_t getSize() const;

    ComplexNVector& operator+=(const ComplexNVector& other);
    ComplexNVector& operator-=(const ComplexNVector& other);
    ComplexNVector& operator*=(const ComplexNumber& scalar);

    ComplexNumber& operator[](size_t index);
    const ComplexNumber& operator[](size_t index) const;

    // Dot product (scalar product) — returns a ComplexNumber
    ComplexNumber dot(const ComplexNVector& other) const;

    friend std::ostream& operator<<(std::ostream& os, const ComplexNVector& v);
    friend std::istream& operator>>(std::istream& is, ComplexNVector& v);
};

ComplexNVector operator+(const ComplexNVector& lhs, const ComplexNVector& rhs);
ComplexNVector operator-(const ComplexNVector& lhs, const ComplexNVector& rhs);
ComplexNVector operator*(const ComplexNVector& v, const ComplexNumber& scalar);
ComplexNVector operator*(const ComplexNumber& scalar, const ComplexNVector& v);

// are perpendicular (dot product == 0)
bool operator|=(const ComplexNVector& lhs, const ComplexNVector& rhs);
