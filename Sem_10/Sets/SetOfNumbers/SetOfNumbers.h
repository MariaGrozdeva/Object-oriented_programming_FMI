#pragma once
#include <iostream>

class SetOfNumbers
{
private:
    unsigned char* data;
    unsigned maxNumber;

    void copyFrom(const SetOfNumbers& other);
    void moveFrom(SetOfNumbers&& other);

    void free();

public:
    SetOfNumbers() = default;
    SetOfNumbers(unsigned n);

    SetOfNumbers(const SetOfNumbers& other);
    SetOfNumbers(SetOfNumbers&& other) noexcept;

    SetOfNumbers& operator=(const SetOfNumbers& other);
    SetOfNumbers& operator=(SetOfNumbers&& other) noexcept;

    ~SetOfNumbers();

private:
    unsigned getBucketsCount() const;
    unsigned getBucketIndex(unsigned number) const;

    unsigned char getMask(unsigned number) const;

public:
    bool add(unsigned number);
    bool remove(unsigned number);
    bool contains(unsigned number) const;

    unsigned getMaxNumber() const;

    void removeAll();

    friend std::ostream& operator<<(std::ostream& os, const SetOfNumbers& set);

    friend SetOfNumbers setUnion(const SetOfNumbers& lhs, const SetOfNumbers& rhs);
    friend SetOfNumbers setIntersection(const SetOfNumbers& lhs, const SetOfNumbers& rhs);
};