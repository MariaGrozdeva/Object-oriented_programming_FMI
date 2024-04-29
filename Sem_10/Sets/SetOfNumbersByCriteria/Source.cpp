#include "SetOfNumbersByCriteria.h"

bool isPrime(unsigned n);

int main()
{
	SetOfNumbersByCriteria s(10, isPrime, [](unsigned n) { return n % 2; });
	std::cout << s << std::endl;

	s.setExclude([](unsigned n) { return n % 2 == 0; });
	std::cout << s << std::endl;
}

bool isPrime(unsigned n)
{
	if (n <= 1)
	{
		return false;
	}

	double sqrtOfN = sqrt(n);
	for (size_t divisorCandidate = 2; divisorCandidate <= sqrtOfN; divisorCandidate++)
	{
		if (n % divisorCandidate == 0)
		{
			return false;
		}
	}
	return true;
}