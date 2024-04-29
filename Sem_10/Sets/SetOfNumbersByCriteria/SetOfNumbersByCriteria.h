#pragma once
#include "../SetOfNumbers/SetOfNumbers.h"
#include <iostream>
#include <functional>

class SetOfNumbersByCriteria : private SetOfNumbers
{
private:
    std::function<bool(unsigned)> incl;
    std::function<bool(unsigned)> excl;

    void fill();

public:
    SetOfNumbersByCriteria(unsigned n, std::function<bool(unsigned)> incl, std::function<bool(unsigned)> excl);

    bool contains(unsigned number) const;

    void setInclude(std::function<bool(unsigned)> incl);
    void setExclude(std::function<bool(unsigned)> excl);

    friend std::ostream& operator<<(std::ostream& os, const SetOfNumbersByCriteria& set);
};