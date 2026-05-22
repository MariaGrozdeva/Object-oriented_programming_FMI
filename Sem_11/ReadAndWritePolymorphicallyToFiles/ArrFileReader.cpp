#include "ArrFileReader.h"
#include <fstream>
#include <stdexcept>

ArrFileReader::ArrFileReader(const MyString& filePath) : FileReader(filePath)
{}

void ArrFileReader::read(int*& arr, size_t& size) const
{
	std::ifstream inFile(filePath.c_str());
	if (!inFile.is_open())
	{
		throw std::runtime_error("File does not open!");
	}

	size = getCharCount(inFile, ' ') + 1;
	delete[] arr;
	arr = new int[size];

	int i = 0;
	inFile.ignore();
	while (!inFile.eof())
	{
		int buff;
		inFile >> buff;
		if (inFile.eof())
		{
			break;
		}
		arr[i++] = buff;
		inFile.ignore();
	}

	inFile.close();
}

int ArrFileReader::getCharCount(std::ifstream& ifs, char ch)
{
	size_t currPos = ifs.tellg();

	if (!ifs.is_open())
	{
		return -1;
	}

	int count = 0;
	while (true)
	{
		char current = ifs.get();
		if (ifs.eof())
		{
			break;
		}
		if (current == ch)
		{
			count++;
		}
	}

	ifs.clear();
	ifs.seekg(currPos);
	return count;
}