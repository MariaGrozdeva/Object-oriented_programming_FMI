#pragma once
#include <cstddef>

class MapKeys0toN
{
public:
    void add(unsigned key, unsigned long long value);
    bool contains(unsigned key) const;
    unsigned long long getValue(unsigned key) const;

private:
    static constexpr size_t n = 100;
    unsigned long long values[n]{ 0 };
};
