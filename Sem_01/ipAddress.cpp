#include <iostream>

// TEACHING-ONLY PURPOSE !
// Reading a different union member than the last written one is UB in standard C++.

union IpAddress
{
	uint32_t address;
	unsigned char octets[4];
};

int main()
{
	IpAddress myAddress;
	myAddress.address = 16777343;
	
	std::cout << (int)myAddress.octets[0] << "." 
	          << (int)myAddress.octets[1] << "." 
	          << (int)myAddress.octets[2] << "." 
	          << (int)myAddress.octets[3];
}
