#include <iostream>
#include <fstream>

void copyFileContent(const char* srcName, const char* destName)
{
	std::ifstream ifs(srcName);
	if (!ifs.is_open())
	{
		return;
	}

	std::ofstream ofs(destName, std::ios::trunc);
	if (!ofs.is_open())
	{
		return;
	}

	constexpr size_t BUFF_SIZE = 1024;
	while (!ifs.eof())
	{
		char buff[BUFF_SIZE];
		ifs.getline(buff, BUFF_SIZE);
		ofs << buff << std::endl;
	}
}

int main()
{
	copyFileContent("src.txt", "dest.txt");
}
