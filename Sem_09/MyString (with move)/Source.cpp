#include "MyString.h"

MyString createString(const char* str)
{
	MyString createdString(str);
	return createdString;
}

int main()
{
	MyString str("Algebra");
	str = createString("OOP");
}