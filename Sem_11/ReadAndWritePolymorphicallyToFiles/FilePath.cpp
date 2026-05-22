#include "FilePath.h"

FilePath::FilePath(const MyString& fileName) 
{
	const char* beg = fileName.c_str();
	const char* end = fileName.c_str() + fileName.getSize();
	const char* iter = end;

	while (iter != beg && *iter != '.')
	{
		iter--;
	}
	
	name = StringView(beg, iter);
	extension = StringView(iter, end);
}

const StringView& FilePath::getName() const
{
	return name;
}

const StringView& FilePath::getExtension() const
{
	return extension;
}