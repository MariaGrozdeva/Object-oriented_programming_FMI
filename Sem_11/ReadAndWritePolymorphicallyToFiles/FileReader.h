#pragma once
#include "MyString.h"

class FileReader
{
public:
	FileReader(const MyString& filePath);
	virtual ~FileReader() = default;
	
	virtual void read(int*& arr, size_t& size) const = 0;
	
protected:
	MyString filePath;
};