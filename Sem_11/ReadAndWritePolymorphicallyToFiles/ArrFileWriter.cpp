#include "ArrFileWriter.h"
#include <fstream>
#include <stdexcept>

ArrFileWriter::ArrFileWriter(const MyString& filePath) : FileWriter(filePath)
{}

void ArrFileWriter::write(const int* arr, size_t size) const
{
	std::ofstream outFile(filePath.c_str());
	if (!outFile.is_open())
	{
		throw std::runtime_error("File does not open!");
	}

	outFile << '[';
	for (size_t i = 0; i < size; i++)
	{
		outFile << arr[i];
		if (i != size - 1)
		{
			outFile << ' ';
		}
	}
	outFile << ']';
	outFile.close();
}
