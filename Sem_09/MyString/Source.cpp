#include "MyString.h"

int main()
{
	MyString str1("OOP");
	MyString str2(" is great!");
	str1 += str2;

	std::cout << str1 << std::endl;
}