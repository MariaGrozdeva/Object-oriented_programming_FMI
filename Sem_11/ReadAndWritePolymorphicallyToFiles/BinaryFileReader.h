#pragma once
#include "FileReader.h"

class BinaryFileReader : public FileReader
{
public:
	BinaryFileReader(const MyString& filePath);
	void read(int*& arr, size_t& size) const override;
	
private:
    static size_t getFileSize(std::ifstream& inFile);
};