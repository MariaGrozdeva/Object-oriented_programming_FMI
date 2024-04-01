#include <iostream>
#include <fstream>

void replaceInFile(char toBeReplaced, char toReplaceWith, std::fstream& file)
{
	while (!file.eof())
	{
		char currentSymbol = file.get();

		if (currentSymbol != toBeReplaced)
			continue;

		file.seekp(-1, std::ios::cur);
		file.put(toReplaceWith);
		file.flush();
	}
}

int main()
{
	std::fstream file("file.txt", std::ios::in | std::ios::out);
	if (!file.is_open())
	{
		std::cout << "Error opening the file!" << std::endl;
		return -1;
	}

	replaceInFile('a', 'X', file);
}
