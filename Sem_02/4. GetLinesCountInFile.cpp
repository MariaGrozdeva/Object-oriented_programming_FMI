#include <iostream>
#include <fstream>

unsigned getCharCountFromFile(std::ifstream& ifs, char ch)
{
    	if (!ifs.is_open())
    	{
		return 0;
    	}
    
	std::streampos currentPos = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	unsigned count = 0;
	char current;
	while (ifs.get(current))
	{
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
	
	myFile.seekg(0, std::ios::end);
        if (myFile.tellg() == 0) // for empty file
        {
                return 0;
        }
        myFile.seekg(0);

        unsigned newLines = getCharCountFromFile(myFile, '\n');
        return newLines + 1;
}

int main()
{
	std::cout << getLinesCount("file.txt");
}
