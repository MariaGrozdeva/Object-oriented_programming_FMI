#include <iostream>
#include <fstream>

int main()
{
	const size_t BUFF_SIZE = 1024;

	std::ifstream file("printMyOwnCode.cpp");
	if (!file.is_open())
	{
		std::cout << "File can't be opened!" << std::endl;
		return -1;
	}

	char buff[BUFF_SIZE];
	while (!file.eof())
	{
		file.getline(buff, BUFF_SIZE);
		std::cout << buff << std::endl;
	}

	file.close();
}
