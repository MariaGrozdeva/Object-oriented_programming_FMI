#pragma once
#include "MyString.h"

class FileWriter
{
public:
	FileWriter(const MyString& filePath);
	virtual ~FileWriter() = default;
	
	virtual void write(const int* arr, size_t size) const = 0;
	
protected:
	MyString filePath;
};