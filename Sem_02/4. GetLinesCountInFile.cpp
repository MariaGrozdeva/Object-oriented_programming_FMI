#include <iostream>
#include <fstream>

unsigned getCharCountFromFile(std::ifstream& ifs, char ch)
{
    	if (!ifs.is_open())
    	{
		return 0;
    	}
    
	size_t currentPos = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	unsigned count = 0;
	while (!ifs.eof())
	{
		char current = ifs.get();
		if (current == ch)
		{
			count++;
		}
	}

	ifs.clear();
	ifs.seekg(currentPos);
	return count;
}

unsigned getLinesCount(const char* fileName)
{
	std::ifstream myFile(fileName);
	if (!myFile.is_open())
	{
		return 0;
	}

	return getCharCountFromFile(myFile, '\n') + 1;
}

int main()
{
	std::cout << getLinesCount("file.txt");
}
