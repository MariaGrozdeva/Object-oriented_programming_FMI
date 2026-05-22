#pragma once
#include "FileWriter.h"

class ArrFileWriter : public FileWriter
{
public:
	ArrFileWriter(const MyString& filePath);
	void write(const int* arr, size_t size) const override;
};