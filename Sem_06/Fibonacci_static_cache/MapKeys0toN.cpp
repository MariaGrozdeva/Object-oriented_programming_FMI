#include "MapKeys0toN.h"
#include <stdexcept>

void MapKeys0toN::add(unsigned key, unsigned value)
{
    if (value == 0)
    {
        return;
    }
    values[key] = value;
}

bool MapKeys0toN::contains(unsigned key) const
{
    return values[key] != 0;
}

unsigned MapKeys0toN::getValue(unsigned key) const
{
    if (!contains(key))
    {
        throw std::invalid_argument("Map does not contain the provided key");
    }
    return values[key];
}