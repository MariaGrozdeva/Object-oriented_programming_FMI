#include "SetOfNumbers.h"
#include <stdexcept>

static constexpr uint8_t bitsInByte = 8;

bool SetOfNumbers::add(unsigned number)
{
    if (number > maxNumber || contains(number))
    {
        return false;
    }

    unsigned bucketIndex = getBucketIndex(number);
    unsigned char mask = getMask(number);
    data[bucketIndex] |= mask;
    return true;
}

bool SetOfNumbers::remove(unsigned number)
{
    if (number > maxNumber || !contains(number))
    {
        return false;
    }

    unsigned bucketIndex = getBucketIndex(number);
    unsigned char mask = getMask(number);
    data[bucketIndex] &= ~mask;
    return true;
}

bool SetOfNumbers::contains(unsigned number) const
{
    if (number > maxNumber)
    {
        return false;
    }

    unsigned bucketIndex = getBucketIndex(number);
    unsigned char mask = getMask(number);
    return (mask & data[bucketIndex]);
}

unsigned SetOfNumbers::getMaxNumber() const
{
    return maxNumber;
}

void SetOfNumbers::removeAll()
{
    unsigned bucketsCount = getBucketsCount();
    for (size_t i = 0; i < bucketsCount; i++)
    {
        data[i] = 0;
    }
}

std::ostream& operator<<(std::ostream& os, const SetOfNumbers& set)
{
    os << "{ ";
    for (unsigned i = 0; i <= set.maxNumber; i++)
    {
        if (set.contains(i))
        {
            os << i << " ";
        }
    }
    os << "}";
    return os;
}

SetOfNumbers setUnion(const SetOfNumbers& lhs, const SetOfNumbers& rhs)
{
    if (lhs.maxNumber != rhs.maxNumber)
    {
        throw std::invalid_argument("Sets must have the same maxNumber");
    }

    SetOfNumbers result(lhs.maxNumber);
    for (size_t i = 0; i < lhs.getBucketsCount(); i++)
    {
        result.data[i] = (lhs.data[i] | rhs.data[i]);
    }
    return result;
}

SetOfNumbers setIntersection(const SetOfNumbers& lhs, const SetOfNumbers& rhs)
{
    if (lhs.maxNumber != rhs.maxNumber)
    {
        throw std::invalid_argument("Sets must have the same maxNumber");
    }

    SetOfNumbers result(lhs.maxNumber);
    for (size_t i = 0; i < lhs.getBucketsCount(); i++)
    {
        result.data[i] = (lhs.data[i] & rhs.data[i]);
    }
    return result;
}

unsigned SetOfNumbers::getBucketsCount() const
{
    return maxNumber / bitsInByte + 1;
}

unsigned SetOfNumbers::getBucketIndex(unsigned number) const
{
    return number / bitsInByte;
}

uint8_t SetOfNumbers::getMask(unsigned number) const
{
    unsigned indInBucket = number % bitsInByte;
    uint8_t mask = 1;
    mask <<= bitsInByte - indInBucket - 1;
    return mask;
}

SetOfNumbers::SetOfNumbers() : data(nullptr), maxNumber(0) {}

SetOfNumbers::SetOfNumbers(unsigned n)
{
    data = new unsigned char[n / bitsInByte + 1];
    for (size_t i = 0; i < (n / bitsInByte + 1); i++)
    {
        data[i] = 0;
    }
    maxNumber = n;
}

SetOfNumbers::SetOfNumbers(const SetOfNumbers& other)
{
    copyFrom(other);
}

SetOfNumbers::SetOfNumbers(SetOfNumbers&& other) noexcept
{
    moveFrom(std::move(other));
}

SetOfNumbers& SetOfNumbers::operator=(const SetOfNumbers& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

SetOfNumbers& SetOfNumbers::operator=(SetOfNumbers&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

SetOfNumbers::~SetOfNumbers()
{
    free();
}

void SetOfNumbers::copyFrom(const SetOfNumbers& other)
{
    maxNumber = other.maxNumber;
    unsigned bucketsCount = other.getBucketsCount();
    data = new unsigned char[bucketsCount];
    for (size_t i = 0; i < bucketsCount; i++)
    {
        data[i] = other.data[i];
    }
}

void SetOfNumbers::moveFrom(SetOfNumbers&& other)
{
    data = other.data;
    maxNumber = other.maxNumber;
    other.data = nullptr;
    other.maxNumber = 0;
}

void SetOfNumbers::free()
{
    delete[] data;
    data = nullptr;
}
