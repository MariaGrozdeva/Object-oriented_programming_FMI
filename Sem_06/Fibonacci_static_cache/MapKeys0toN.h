#pragma once
#include <iostream>

class MapKeys0toN
{
public:
    void add(unsigned key, unsigned value);
    bool contains(unsigned key) const;
    unsigned getValue(unsigned key) const;

private:
    static constexpr size_t n = 100;
    unsigned values[n]{ 0 };
};