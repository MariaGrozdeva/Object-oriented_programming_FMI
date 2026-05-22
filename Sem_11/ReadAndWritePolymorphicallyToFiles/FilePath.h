#pragma once
#include "StringView.h"

class FilePath
{
public:
	FilePath(const MyString& fileName);
	
	const StringView& getName() const;
	const StringView& getExtension() const;
	
private:
	StringView name;
	StringView extension;
};