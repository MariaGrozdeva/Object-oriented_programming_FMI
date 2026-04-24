#pragma once

template<typename FunctionOne, typename FunctionTwo>
class IntFunctionAverage
{
public:
    IntFunctionAverage(const FunctionOne& firstFunc, const FunctionTwo& secondFunc) : firstFunc(firstFunc), secondFunc(secondFunc)
    {}

    double average(int x) const
    {
        return (firstFunc(x) + secondFunc(x)) / 2.0;
    }
    
private:
    FunctionOne firstFunc;
    FunctionTwo secondFunc;
};