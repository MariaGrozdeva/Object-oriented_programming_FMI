#include "ComplexNVector.h"
#include <stdexcept>

ComplexNVector::ComplexNVector(size_t size) : size(size)
{
    data = new ComplexNumber[size]; // calls ComplexNumber(0, 0) for each
}

ComplexNVector::ComplexNVector(const ComplexNVector& other) : data(nullptr)
{
    if (other.data != nullptr)
    {
        data = new ComplexNumber[other.size];
        for (size_t i = 0; i < other.size; i++)
        {
            data[i] = other.data[i];
        }
    }
    size = other.size;
}

ComplexNVector& ComplexNVector::operator=(const ComplexNVector& other)
{
    if (this != &other)
    {
        ComplexNumber* newData = nullptr;
        if (other.data != nullptr)
        {
            newData = new ComplexNumber[other.size];
            for (size_t i = 0; i < other.size; i++)
            {
                newData[i] = other.data[i];
            }
        }

        delete[] data;
        data = newData;
        size = other.size;
    }
    return *this;
}

ComplexNVector::~ComplexNVector()
{
    delete[] data;
}

size_t ComplexNVector::getSize() const
{
    return size;
}

ComplexNVector& ComplexNVector::operator+=(const ComplexNVector& other)
{
    if (size != other.size)
        throw std::invalid_argument("Vectors must have equal sizes");

    for (size_t i = 0; i < size; i++)
        data[i] += other.data[i];

    return *this;
}

ComplexNVector& ComplexNVector::operator-=(const ComplexNVector& other)
{
    if (size != other.size)
        throw std::invalid_argument("Vectors must have equal sizes");

    for (size_t i = 0; i < size; i++)
        data[i] -= other.data[i];

    return *this;
}

ComplexNVector& ComplexNVector::operator*=(const ComplexNumber& scalar)
{
    for (size_t i = 0; i < size; i++)
        data[i] *= scalar;

    return *this;
}

ComplexNumber& ComplexNVector::operator[](size_t index)
{
    return data[index];
}

const ComplexNumber& ComplexNVector::operator[](size_t index) const
{
    return data[index];
}

// Uses conjugate of rhs elements — standard Hermitian inner product
ComplexNumber ComplexNVector::dot(const ComplexNVector& other) const
{
    if (size != other.size)
        throw std::invalid_argument("Vectors must have equal sizes");

    ComplexNumber result(0, 0);
    for (size_t i = 0; i < size; i++)
    {
        ComplexNumber conjugate = other.data[i].getComplexConjugate();
        result += data[i] * conjugate;
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const ComplexNVector& v)
{
    os << "[ ";
    for (size_t i = 0; i < v.size; i++)
        os << v.data[i] << ' ';
    os << "]";
    return os;
}

std::istream& operator>>(std::istream& is, ComplexNVector& v)
{
    for (size_t i = 0; i < v.size; i++)
        is >> v.data[i];
    return is;
}

ComplexNVector operator+(const ComplexNVector& lhs, const ComplexNVector& rhs)
{
    ComplexNVector result(lhs);
    result += rhs;
    return result;
}

ComplexNVector operator-(const ComplexNVector& lhs, const ComplexNVector& rhs)
{
    ComplexNVector result(lhs);
    result -= rhs;
    return result;
}

ComplexNVector operator*(const ComplexNVector& v, const ComplexNumber& scalar)
{
    ComplexNVector result(v);
    result *= scalar;
    return result;
}

ComplexNVector operator*(const ComplexNumber& scalar, const ComplexNVector& v)
{
    return v * scalar;
}

bool operator|=(const ComplexNVector& lhs, const ComplexNVector& rhs)
{
    if (lhs.getSize() != rhs.getSize())
        return false;

    ComplexNumber result = lhs.dot(rhs);
    // Perpendicular if dot product is (0, 0)
    return result.getReal() == 0 && result.getIm() == 0;
}
