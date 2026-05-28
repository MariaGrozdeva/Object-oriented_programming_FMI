#include <iostream>
#include <fstream>
#include <new>

class DynamicHexArray
{
private:
    uint8_t *data;
    size_t used;
    size_t allocated;
    bool isObjValid = true;

    static size_t nextPowerOfTwo(size_t size)
    {
        if (size == 0)
        {
            return 1;
        }

        size--;
        size |= size >> 1;
        size |= size >> 2;
        size |= size >> 4;
        size |= size >> 8;
        size |= size >> 16;
        size |= size >> 32;
        return ++size;
    }

    bool grow()
    {
        uint8_t *newArray = new(std::nothrow) uint8_t[allocated * 2];
        if (newArray == nullptr)
        {
            return false;
        }
        for (int i = 0; i < used; i++)
        {
            newArray[i] = data[i];
        }
        delete[] data;
        data = newArray;
        allocated *= 2;
        return true;
    }

    bool isFull() const
    {
        return used == allocated;
    }

public:
    explicit DynamicHexArray(size_t size)
    {
        size = nextPowerOfTwo(size);
        data = new(std::nothrow) uint8_t[size];
        if (data == nullptr)
        {
            isObjValid = false;
        }
        // Not the best way to handle it, but without exceptions this the best way I came up with.
        used = 0;
        allocated = size;
    }

    ~DynamicHexArray()
    {
        delete[] data;
        data = nullptr;
        used = 0;
        allocated = 0;
    }

    bool getIsObjValid() const
    {
        return isObjValid;
    }

    size_t getSize() const
    {
        return used;
    }

    bool append(const uint8_t value)
    {
        data[used++] = value;
        bool res = true;
        if (isFull())
        {
            res = grow();
        }
        return res;
    }

    bool modify(const size_t index, const uint8_t value)
    {
        if (index >= used)
        {
            return false;
        }
        data[index] = value;
        return true;
    }

    bool fillFromFile(std::ifstream &file)
    {
        while (file.good())
        {
            uint8_t byte;
            file.read(reinterpret_cast<char *>(&byte), sizeof(byte));
            if (!file.good())
            {
                break;
            }
            if (!append(byte))
            {
                return false;
            }
        }

        return true;
    }

    bool writeArrayToFile(std::ofstream &file) const
    {
        if (!file.write(reinterpret_cast<const char *>(data), used))
        {
            return false;
        }
        return true;
    }

    void print() const
    {
        for (int i = 0; i < used; i++)
        {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << " ";
        }
        std::cout << "\n";
        for (int i = 0; i < used; i++)
        {
            if ((data[i] >= 'A' && data[i] <= 'Z') || (data[i] >= 'a' && data[i] <= 'z'))
            {
                std::cout << data[i] << "  ";
            } else
            {
                std::cout << ".. ";
            }
        }
        std::cout << std::endl;
    }
};

bool readHexByte(unsigned int& byte)
{
    std::cin >> std::hex >> byte;
    if (!std::cin)
    {
        std::cout << "Invalid input!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (byte > 0xFF)
    {
        std::cout << "Invalid input!\n";
        return false;
    }
    return true;
}

size_t getFileSize(std::ifstream &file)
{
    const std::streampos currentPos = file.tellg();
    file.seekg(0, std::ios::end);
    const size_t fileSize = static_cast<size_t>(file.tellg());
    file.seekg(currentPos);
    return fileSize;
}

int main()
{
    constexpr int x = 25409;
    constexpr short MAX_COMMAND_LEN = 100;
    constexpr int MAX_PATH_LEN = 1024;
    std::ofstream oFile("myData.bin", std::ios::binary | std::ios::trunc);
    if (!oFile.is_open())
    {
        std::cout << "File can't be opened!";
        return -1;
    }
    if (!oFile.write(reinterpret_cast<const char *>(&x), sizeof(x)))
    {
        std::cout << "Writing failed!";
        return -1;
    }
    oFile.close();

    char path[MAX_PATH_LEN];
    std::cout << "Enter the path to the file: ";
    std::cin.getline(path, MAX_PATH_LEN);
    if (!std::cin)
    {
        std::cout << "Invalid path!";
        return -1;
    }
    std::ifstream iFile(path, std::ios::binary);
    if (!iFile.is_open())
    {
        std::cout << "File can't be opened!";
        return -1;
    }

    const size_t fileSize = getFileSize(iFile);
    DynamicHexArray array(fileSize);
    if (!array.getIsObjValid())
    {
        std::cout << "Memory allocation failed!";
        return -1;
    }
    if (!array.fillFromFile(iFile))
    {
        std::cout << "Reading failed!";
        return -1;
    }
    iFile.close();
    std::cout << "File loaded successfully. Size: " << fileSize << " bytes." << std::endl;
    array.print();

    char buff[MAX_COMMAND_LEN];
    while (true)
    {
        std::cin.getline(buff, MAX_COMMAND_LEN);
        if (!std::cin)
        {
            std::cout << "Invalid command!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (strcmp(buff, "view") == 0)
        {
            array.print();
        } else if (strcmp(buff, "add") == 0)
        {
            std::cout << "Enter hex byte to add: ";
            unsigned int byte;
            if (!readHexByte(byte))
            {
                continue;
            }
            if (array.append(static_cast<uint8_t>(byte)) == false)
            {
                std::cout << "Append failed!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            std::cout << "Byte added successfully!" << std::endl;
        } else if (strcmp(buff, "change") == 0)
        {
            unsigned pos = 0;
            std::cout << "Enter index: ";
            std::cin >> pos;
            if (!std::cin)
            {
                std::cout << "Invalid input!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter new hex byte: ";
            unsigned int byte;
            if (!readHexByte(byte))
            {
                continue;
            }
            if (array.modify(pos, static_cast<uint8_t>(byte)) == false)
            {
                std::cout << "Writing failed!\n";
                continue;
            }

            std::cout << "Byte changed successfully!" << std::endl;
        } else if (strcmp(buff, "save as") == 0)
        {
            std::cout << "Enter new path: ";
            std::cin.getline(path, MAX_PATH_LEN);
            if (!std::cin)
            {
                std::cout << "Invalid path!";
            }

            std::ofstream newFile(path, std::ios::binary);
            if (!newFile.is_open())
            {
                std::cout << "File can't be opened!";
                return -1;
            }

            if (!array.writeArrayToFile(newFile))
            {
                std::cout << "Writing failed!";
                newFile.close();
                return -1;
            }

            std::cout << "File saved successfully!" << std::endl;
            newFile.close();
            break;
        } else if (strcmp(buff, "save") == 0)
        {
            std::ofstream originalFile(path, std::ios::binary);
            if (!originalFile.is_open())
            {
                std::cout << "File can't be opened!";
                return -1;
            }
            if (!array.writeArrayToFile(originalFile))
            {
                std::cout << "Writing failed!";
                originalFile.close();
                return -1;
            }
            originalFile.close();
            std::cout << "File saved successfully!" << std::endl;
            break;
        } else if (strcmp(buff, "exit") == 0)
        {
            std::cout << "Exiting...";
            return 0;
        } else
        {
            std::cout << "Invalid command!\n";
        }
    }

    return 0;
}
