#include <iostream>

// TEACHING-ONLY PURPOSE !
// Reading a different union member than the last written one is UB in standard C++.

bool isLittleEndian()
{
    union endiannessTest
    {
	uint32_t n = 1;
	unsigned char bytes[4];
    } myTest;
	
    return myTest.bytes[0];
}

int main()
{
    std::cout << isLittleEndian();
}
