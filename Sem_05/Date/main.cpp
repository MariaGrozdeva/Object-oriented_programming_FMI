#include "Date.h"

int main()
{
    Date d(26, 3, 2024);
    d.serialize(std::cout);
    
    d.goNextDay();
    d.goNextDay();
    d.serialize(std::cout);

    d.goNextDay();
    d.goNextDay();
    d.goNextDay();
    d.goNextDay();
    d.serialize(std::cout);

    std::cout << compareDates({ 1,1,2024 }, { 31, 12, 2023 }) << std::endl;
}