#pragma once
#include <iostream>
#include <cstdint>

class SetOfNumbers
{
public:
    SetOfNumbers();
    SetOfNumbers(unsigned n);

    SetOfNumbers(const SetOfNumbers& other);
    SetOfNumbers& operator=(const SetOfNumbers& other);
    
    SetOfNumbers(SetOfNumbers&& other) noexcept;
    SetOfNumbers& operator=(SetOfNumbers&& other) noexcept;

    ~SetOfNumbers();
    
    bool add(unsigned number);
    bool remove(unsigned number);
    bool contains(unsigned number) const;

    unsigned getMaxNumber() const;

    void removeAll();

    friend std::ostream& operator<<(std::ostream& os, const SetOfNumbers& set);

    friend SetOfNumbers setUnion(const SetOfNumbers& lhs, const SetOfNumbers& rhs);
    friend SetOfNumbers setIntersection(const SetOfNumbers& lhs, const SetOfNumbers& rhs);

private:
    uint8_t* data;
    unsigned maxNumber;

    void copyFrom(const SetOfNumbers& other);
    void moveFrom(SetOfNumbers&& other);
    void free();
    
    unsigned getBucketsCount() const;
    unsigned getBucketIndex(unsigned number) const;

    uint8_t getMask(unsigned number) const;
};
