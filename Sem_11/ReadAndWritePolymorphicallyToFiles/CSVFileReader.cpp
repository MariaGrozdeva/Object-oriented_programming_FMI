#include "CSVFileReader.h"
#include <fstream>

CSVFileReader::CSVFileReader(const MyString& filePath) : FileReader(filePath)
{}

void CSVFileReader::read(int*& arr, size_t& size) const
{
	std::ifstream inFile(filePath.c_str());
	if (!inFile.is_open())
	{
		throw std::runtime_error("File does not open!");
	}

	size = getCharCount(inFile, ',') + 1;
	delete[] arr;
	arr = new int[size];
	
	int i = 0;
	while (!inFile.eof())
	{
		int buff;
		inFile >> buff;
		arr[i++] = buff;
		inFile.ignore();
	}
	
	inFile.close();
}

int CSVFileReader::getCharCount(std::ifstream& ifs, char ch)
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