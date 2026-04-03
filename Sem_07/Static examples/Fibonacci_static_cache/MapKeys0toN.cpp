#include "MapKeys0toN.h"
#include <stdexcept>

void MapKeys0toN::add(unsigned key, unsigned long long value)
{
    if (key >= n)
    {
        throw std::out_of_range("Key out of range");
    }

    if (value == 0)
    {
        return;
    }

    values[key] = value;
}

bool MapKeys0toN::contains(unsigned key) const
{
    if (key >= n)
    {
        return false;
    }

    return values[key] != 0;
}

unsigned long long MapKeys0toN::getValue(unsigned key) const
{
    if (key >= n)
    {
        throw std::out_of_range("Key out of range");
    }

    if (!contains(key))
    {
        throw std::invalid_argument("Map does not contain the provided key");
    }

    return values[key];
}
