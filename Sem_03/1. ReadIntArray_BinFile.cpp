#include <iostream>
#include <fstream>

std::streampos getFileSize(std::ifstream& file)
{
	std::streampos currentPos = file.tellg();
	file.seekg(0, std::ios::end);

	size_t fileSize = static_cast<size_t>(file.tellg());
	file.seekg(currentPos);

	return fileSize;
}

int main()
{
	std::ifstream ifs("file.dat", std::ios::binary);
	if (!ifs.is_open())
	{
		return -1;
	}

	size_t fileSize = getFileSize(ifs);
	size_t arrSize = fileSize / sizeof(int);

	int* arr = new int[arrSize];
	ifs.read(reinterpret_cast<char*>(arr), fileSize);

	for (size_t i = 0; i < arrSize; i++)
	{
		std::cout << arr[i] << ' ';
	}

	delete[] arr;
	ifs.close();
}
