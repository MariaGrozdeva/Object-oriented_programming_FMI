//hex viewer

#include <iostream>
#include <fstream>
#include <iomanip>

const unsigned int MAX_SIZE = 1024;

struct HexViewerFile
{
    unsigned char* data = nullptr;
    size_t dataSize = 0;
};

int initStartFile()
{
    std::ofstream file("myData.dat", std::ios::binary);
    if (!file)
    {
        std::cout << "File could not be opened!" << std::endl;
        return -1;
    }

    char x = 'a';
    file.write((const char*)&x, sizeof(x));

    file.close();

    if (!file.fail())
    {
        std::cout << "File saved succesfully!" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Error!" << std::endl;
        return -1;
    }
}

int getFileSize(std::ifstream& file)
{
    int currentPos = file.tellg();
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    file.seekg(currentPos, std::ios::beg);
    return size;
}

HexViewerFile readBinaryFile(const char* fileName)
{
    HexViewerFile myData;

    std::ifstream file (fileName, std::ios::binary);
    if (!file)
    {
        std::cout << "File could not be opened!" << std::endl;
        return myData;
    }

    myData.dataSize = getFileSize(file);
    myData.data = new unsigned char[myData.dataSize + 1];
    file.read((char*)myData.data, myData.dataSize);
    myData.data[myData.dataSize] = '\0';
    file.close();

    return myData;
}

void freeHexViewerFile(HexViewerFile& d)
{
    delete[] d.data;
    d.dataSize = 0;
}

bool isValidSymbol(char ch)
{
    return ch >= 'a' && ch <= 'z' ||
        ch >= 'A' && ch <= 'Z' ||
        ch >= '0' && ch <= '9';
}

void printData(const HexViewerFile& myData)
{
    for (size_t i = 0; i < myData.dataSize; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)myData.data[i] << ' ';
    }
    std::cout << std::endl;

    for (size_t i = 0; i < myData.dataSize; i++)
    {
        if (isValidSymbol(myData.data[i]))
        {
            std::cout << myData.data[i] << "  ";
        }
        else
        {
            std::cout << ".. ";
        }
    }
    std::cout << std::endl;
}

// strcpy doesn't work with unsigned char
void mystrcpy(unsigned char* dest, size_t size, unsigned char* src)
{
    for (int i = 0; i < size; ++i)
    {
        dest[i] = src[i];
    }
}

void addByte(HexViewerFile& myData, char byte)
{
    size_t newSize = myData.dataSize + 1;
    unsigned char* newArr = new unsigned char[newSize + 1];
    mystrcpy(newArr, myData.dataSize, myData.data);
    newArr[myData.dataSize] = byte;
    newArr[newSize] = '\0';

    delete[] myData.data;
    myData.data = newArr;
    myData.dataSize = newSize;
}

void changeByte(HexViewerFile& myData, size_t ind, char ch)
{
    if (ind > myData.dataSize || ind < 0)
    {
        std::cout << "Index out of range!" << std::endl;
        return;
    }

    myData.data[ind] = ch;
}

void saveFile(HexViewerFile& myData, const char* dest)
{
    std::ofstream file(dest, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }

    file.write((const char*)myData.data, myData.dataSize);

    file.close();
}

int main()
{
    // create a file to read from
    //initStartFile();

    //user must enter file name
    char fileName[MAX_SIZE];
    std::cout << "Enter file name: ";
    std::cin >> fileName;

    HexViewerFile myData = readBinaryFile(fileName);
    if (myData.dataSize > 0)
        std::cout << "Size: " << myData.dataSize << std::endl;
    else
        return -1;

    printData(myData);

    char command[MAX_SIZE];
    while (true)
    {
        std::cout << "Enter command: ";
        // because save as is two words
        std::cin >> command;

        if (strcmp(command, "view") == 0)
        {
            printData(myData);
        }
        else if (strcmp(command, "add") == 0)
        {
            char ch;
            std::cout << "Enter char: ";
            std::cin >> ch;
            addByte(myData, ch);
        }
        else if (strcmp(command, "change") == 0)
        {
            size_t ind;
            char ch;
            std::cout << "Enter index and char: ";
            std::cin >> ind >> ch;
            changeByte(myData, ind, ch);
        }
        else if (strcmp(command, "save") == 0)
        {
            saveFile(myData, fileName);
            break;
        }
        else if (strcmp(command, "save_as") == 0)
        {
            char newFile[MAX_SIZE];
            std::cout << "Enter file name: ";
            std::cin >> newFile;
            saveFile(myData, newFile);
            break;
        }
        else
            std::cout << "There is no such command!" << std::endl;
    }

    freeHexViewerFile(myData);
}
