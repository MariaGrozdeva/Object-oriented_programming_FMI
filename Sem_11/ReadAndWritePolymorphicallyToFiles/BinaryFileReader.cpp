#include "BinaryFileReader.h"
#include <fstream>
#include <stdexcept>

BinaryFileReader::BinaryFileReader(const MyString& filePath) : FileReader(filePath)
{}

void BinaryFileReader::read(int*& arr, size_t& size) const
{
	std::ifstream inFile(filePath.c_str(), std::ios::binary);
	if (!inFile.is_open())
	{
		throw std::runtime_error("File does not open!");
	}

	size = getFileSize(inFile) / sizeof(int);
	delete[] arr;
	arr = new int[size];

	inFile.read((char*)arr, size * sizeof(int));
	inFile.close();
}

size_t BinaryFileReader::getFileSize(std::ifstream& inFile)
{
	size_t currPos = inFile.tellg();
	inFile.seekg(0, std::ios::end);
	size_t res = inFile.tellg();
	inFile.seekg(currPos);

	return res;
}