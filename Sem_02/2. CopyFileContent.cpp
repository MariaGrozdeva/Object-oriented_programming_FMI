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
    char buff[BUFF_SIZE];

    while (ifs.getline(buff, BUFF_SIZE))
    {
        ofs << buff << '\n';
    }
}

int main()
{
    copyFileContent("src.txt", "dest.txt");
}
