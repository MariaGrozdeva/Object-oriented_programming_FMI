#include <iostream>
#include "IntFunctionAverage.hpp"
#include "FunctionFromFile.hpp"

int main()
{
    char filePath[1024]{};
    std::cout << "Enter file path:" << std::endl;
    std::cin.getline(filePath, 1024);

    FunctionFromFile func(filePath);
    if (!func.good())
    {
        std::cout << "Invalid file path" << std::endl;
        return -1;
    }

    IntFunctionAverage<FunctionFromFile, int (*)(int)> f(func, [](int x) { return x; });

    while (true)
    {
        int num = 0;
        std::cout << "Enter value for the functions:" << std::endl;
        std::cin >> num;
        std::cout << "Average: " << f.average(num) << std::endl;
    }
}