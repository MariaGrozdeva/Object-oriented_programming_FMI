#include "StringPool.h"

int main()
{
	StringPool dict1;
	((dict1 *= "Ivan") *= "Petur") *= "Alex";
	std::cout << dict1 << std::endl; // {Alex, Ivan, Petur}
	std::cout << dict1["Alex"] << ' ' << dict1["abc"] << std::endl; // 1 0

	StringPool dict2;
	((dict2 *= "Niq") *= "Alex");

	StringPool result1 = dict1 + dict2;
	std::cout << result1 << std::endl; // {Alex, Ivan, Niq, Petur}

	StringPool result2 = dict1 - dict2;
	std::cout << result2 << std::endl; // {Ivan, Petur}

	"NewWord" >> result2;
	result2 /= "NonExistingWord";
	std::cout << result2 << std::endl;  // {Ivan, NewWord, Petur}

	"Job" >> result2;
	std::cout << result2 << std::endl;  // {Ivan, Job, NewWord, Petur}
}