#include <iostream>
#include <fstream>

void replaceInFile(char toBeReplaced, char toReplaceWith, std::fstream& file)
{
    char currentSymbol;

    while (file.get(currentSymbol))
    {
        if (currentSymbol == toBeReplaced)
        {
            std::streampos pos = file.tellg(); // position after reading currentSymbol

            file.seekp(pos - std::streamoff(1));
            file.put(toReplaceWith);
            file.flush();

            file.seekg(pos);
        }
    }
}

int main()
{
    std::fstream file("file.txt", std::ios::in | std::ios::out);
    if (!file.is_open())
    {
        std::cout << "Error opening the file!" << std::endl;
        return -1;
    }

    replaceInFile('a', 'X', file);
}
