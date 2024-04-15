#include "NVector.h"
#include <new>

int main()
{
    	try
    	{
	    	NVector v1(3), v2(3);
	    	for (size_t i = 0; i < v1.getSize(); i++)
	    	{
			v1[i] = v2[i] = i;
	    	}
	    
	    	NVector v3 = v1 + v2;
	    	std::cout << v3;
    	}
    	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
