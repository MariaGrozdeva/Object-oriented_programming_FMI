#include <iostream>
#include <fstream>

size_t getFileSize(std::ifstream& file)
{
	unsigned int currentPos = file.tellg();
	file.seekg(0, std::ios::end);

	size_t fileSize = file.tellg();
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
