#include "MapKeys0toN.h"

unsigned long long fib(unsigned n)
{
    if (n <= 2)
    {
        return 1;
    }
    
    static MapKeys0toN cache;

    if (cache.contains(n))
    {
        return cache.getValue(n);
    }

    unsigned long long res = fib(n - 1) + fib(n - 2);
    cache.add(n, res);
    return res;
}

int main()
{
	std::cout << fib(30) << std::endl;
	std::cout << fib(30) << std::endl;
}