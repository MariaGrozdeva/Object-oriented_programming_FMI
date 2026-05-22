#pragma once
#include "FileReader.h"

class CSVFileReader : public FileReader
{
public:
	CSVFileReader(const MyString& filePath);
	void read(int*& arr, size_t& size) const override;
	
private:
    static int getCharCount(std::ifstream& ifs, char ch);
};