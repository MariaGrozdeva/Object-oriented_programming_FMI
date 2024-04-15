#include "NVector.h"
#include <cassert>
#include <stdexcept>

NVector::NVector(size_t size) : size(size)
{
    data = new int[size];
    for (size_t i = 0; i < size; i++)
    {
        data[i] = 0;
    }
}

size_t NVector::getSize() const
{
    return size;
}

NVector& NVector::operator+=(const NVector& other)
{
    if (size != other.size)
    {
        throw std::invalid_argument("Vectors must have equal sizes");
    }

    for (size_t i = 0; i < size; i++)
    {
        data[i] += other.data[i];
    }
    return *this;
}

NVector& NVector::operator-=(const NVector& other)
{
    if (size != other.size)
    {
        throw std::invalid_argument("Vectors must have equal sizes");
    }

    for (size_t i = 0; i < size; i++)
    {
        data[i] -= other.data[i];
    }
    return *this;
}

NVector& NVector::operator*=(size_t scalar)
{
    for (size_t i = 0; i < size; i++)
    {
        data[i] *= scalar;
    }
    return *this;
}

int& NVector::operator[](size_t index)
{
    return data[index];
}

int NVector::operator[](size_t index) const
{
    return data[index];
}

std::ostream& operator<<(std::ostream& os, const NVector& v)
{
    os << "[ ";
    for (size_t i = 0; i < v.size; i++)
    {
        os << v[i] << ' ';
    }
    os << " ]";

    return os;
}

std::istream& operator>>(std::istream& is, NVector& v)
{
    for (size_t i = 0; i < v.size; i++)
    {
        is >> v[i];
    }

    return is;
}

NVector operator+(const NVector& lhs, const NVector& rhs)
{
    NVector result(lhs);
    result += rhs;
    return result;
}
NVector operator-(const NVector& lhs, const NVector& rhs)
{
    NVector result(lhs);
    result -= rhs;
    return result;
}

NVector operator*(const NVector& v, size_t scalar)
{
    NVector result(v);
    result *= scalar;
    return result;
}
NVector operator*(size_t scalar, const NVector& v)
{
    return v * scalar;
}

bool operator||(const NVector& lhs, const NVector& rhs)
{
    if (lhs.getSize() != rhs.getSize())
    {
        return false;
    }

    for (size_t i = 0; i < lhs.getSize() - 1; i++)
    {
        if (lhs[i] * rhs[i + 1] != lhs[i + 1] * rhs[i])
        {
            return false;
        }
    }
    return true;
}

bool operator|=(const NVector& lhs, const NVector& rhs)
{
    if (lhs.getSize() != rhs.getSize())
    {
        return false;
    }

    //scalar product
    int res = 0;
    for (size_t i = 0; lhs.getSize(); i++)
    {
        res += lhs[i] * rhs[i];
    }
    return res == 0; // perpendicular if their scalar product is zero
}

NVector::NVector(const NVector& other)
{
    copyFrom(other);
}
NVector& NVector::operator=(const NVector& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
NVector::~NVector()
{
    free();
}

void NVector::copyFrom(const NVector& other)
{
    data = new int[other.size];
    size = other.size;

    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}
void NVector::free()
{
    delete[] data;
}
