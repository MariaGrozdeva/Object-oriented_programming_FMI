#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

struct HexViewerFile
{
	unsigned char* data;
	size_t dataSize;
};

const int MAX_PATH_SIZE = 1024;

void freeHexViewerFile(HexViewerFile& file)
{
	delete[] file.data;
	file.dataSize = 0;
}

size_t getFileSize(std::ifstream& file)
{
	unsigned int currentPos = file.tellg();
	file.seekg(0, std::ios::end);

	size_t fileSize = file.tellg();
	file.seekg(currentPos);

	return fileSize;
}

HexViewerFile init(const char* filePath)
{
	std::ifstream ifs(filePath, std::ios::binary);
	HexViewerFile myFile;

	if (!ifs.is_open())
	{
		myFile.data = nullptr;
		myFile.dataSize = 0;
		return myFile;
	}

	myFile.dataSize = getFileSize(ifs);
	myFile.data = new unsigned char[myFile.dataSize];
	ifs.read((char*)myFile.data, myFile.dataSize);

	ifs.close();
	return myFile;
}

bool isValidSymbol(char ch)
{
	return ch >= 'a' && ch <= 'z' ||
		ch >= 'A' && ch <= 'Z' ||
		ch >= '0' && ch <= '9';
}

void print(const HexViewerFile& myFile)
{
    if(myFile.dataSize == 0)
    {
        std::cout << "file empty" << std::endl;
        return;
    }

	for (size_t i = 0; i < myFile.dataSize; i++)
	{
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)myFile.data[i] << ' ';
	}
	std::cout << std::endl;

	for (size_t i = 0; i < myFile.dataSize; i++)
	{
		if (isValidSymbol(myFile.data[i]))
		{
			std::cout << myFile.data[i] << "  ";
		}
		else
		{
			std::cout << ".. ";
		}
	}
	std::cout << std::endl;
}

int getSize(unsigned char* hexVal)
{
    int size = 1;
    while(hexVal[size - 1] != '\0')
    {
        hexVal++;
        size++;
    }

    return size ;
}

int hexToDec(unsigned char* hexVal)
{
    int len = getSize(hexVal);
    int base = 1;
    int dec_val = 0;
 
    for (int i = len - 1; i >= 0; i--) {
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;
 
            base = base * 16;
        }
 
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
            dec_val += (int(hexVal[i]) - 55) * base;

             base = base * 16;
        }
    }
    return dec_val;
}

void change(HexViewerFile& myFile)
{
    int position;
    std::cin >> position;

    // Check that position is within the bounds of the data array
    if (position < 0 || position >= myFile.dataSize) {
        std::cout << "Error: position " << position << " is out of bounds\n";
        return;
    }

    // Read in the byte input as a hexadecimal value
    unsigned int byteInput;
    std::cin >> std::hex >> byteInput;

    // Convert the hexadecimal value to an unsigned char and store it in the data array
    myFile.data[position] = static_cast<unsigned char>(byteInput);
}

void add(HexViewerFile& myFile)
{
    //asumes that the number is corectly inputed in hexadecimal
    unsigned char byteInput[2];
    std::cin >> byteInput;
    int decInput = hexToDec(byteInput);

    myFile.data[myFile.dataSize] = decInput;
    myFile.dataSize += sizeof(char);
}

void save(const HexViewerFile& myFile, const char* savePath)
{
	std::ofstream file(savePath, std::ios::binary);

	if (!file.is_open())
	{
        std::cout << "File could notbe opened" << std::endl;
        return;
	}

    file.write((const char*)myFile.data, myFile.dataSize);
	file.close();
}

void userInput()
{
    char command[10], filePath[MAX_PATH_SIZE];
    std::cout << "Enter a file path:" << std::endl;

    std::cin >> filePath;
    HexViewerFile myFile = init(filePath);
    std::cout << "File loaded successfully. Size: " << myFile.dataSize << " bytes" << std::endl << std::endl;

    std::cout << "Enter 'exit' if you don't want to save the file." << std::endl;
    do
    {
        std::cin >> command;
        if(!strcmp(command,"view"))
          	print(myFile);
        else if(!strcmp(command,"add"))
            add(myFile);
        else if(!strcmp(command,"change"))
            change(myFile);
        else if(!strcmp(command,"save"))
        {
            save(myFile, filePath);
            break;
        }
        else if(!strcmp(command,"save_as"))
        {
            char path[MAX_PATH_SIZE];
            std::cout << "Enter the file directory" << std::endl;
            std::cin >> path;
            save(myFile, path);
            break;
        }
        else if(!strcmp(command,"exit"))
            break;
        else
            std::cout << "Invalid comand" << std::endl;
    }    
    while(true);
}

int main()
{
    userInput();
}