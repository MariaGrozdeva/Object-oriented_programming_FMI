#include "AnimalCollection.h"
#include <fstream>

int main()
{
    	std::ifstream ifs("animals.txt");
    	if (!ifs.is_open())
    	{   
        	return -1;
    	}
    
    	size_t animalsCount;
    	ifs >> animalsCount;
    
	AnimalCollection coll;
    	for (size_t i = 0; i < animalsCount; ++i)
    	{
        	coll.createAnimal(ifs);
    	}
    
    	ifs.close();
    
    	for (size_t i = 0; i < animalsCount; i++)
	{
		coll[i]->sayHello();
	}
}
