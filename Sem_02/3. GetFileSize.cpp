#include <iostream>
#include <fstream>

std::streampos getFileSize(std::ifstream& file)
{
	std::streampos currentPos = file.tellg();
	file.seekg(0, std::ios::end);

	std::streampos fileSize = file.tellg();
	file.seekg(currentPos);

	return fileSize;
}

int main()
{

}
