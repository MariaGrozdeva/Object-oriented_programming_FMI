#include "SetOfNumbersByCriteria.h"

SetOfNumbersByCriteria::SetOfNumbersByCriteria(unsigned n, std::function<bool(unsigned)> incl, std::function<bool(unsigned)> excl) : SetOfNumbers(n)
{
    this->incl = incl;
    this->excl = excl;

    for (size_t i = 0; i <= n; i++)
    {
        if (incl(i) && !excl(i))
        {
            add(i);
        }
    }
}

bool SetOfNumbersByCriteria::contains(unsigned number) const
{
    return contains(number);
}

void SetOfNumbersByCriteria::setInclude(std::function<bool(unsigned)> incl)
{
    this->incl = incl;
    removeAll();
    fill();
}
void SetOfNumbersByCriteria::setExclude(std::function<bool(unsigned)> excl)
{
    this->excl = excl;
    removeAll();
    fill();
}

std::ostream& operator<<(std::ostream& os, const SetOfNumbersByCriteria& set)
{
    os << static_cast<const SetOfNumbers&>(set);
    return os;
}

void SetOfNumbersByCriteria::fill()
{
    for (size_t i = 0; i < SetOfNumbers::getMaxNumber(); i++)
    {
        if (incl(i) && !excl(i))
        {
            add(i);
        }
        else
        {
            remove(i);
        }
    }
}