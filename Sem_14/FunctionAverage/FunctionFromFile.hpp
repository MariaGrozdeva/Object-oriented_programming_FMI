#include <fstream>

class FunctionFromFile
{
public:
    static unsigned getFileSize(std::ifstream& ifs)
    {
        size_t currentPos = ifs.tellg();
        ifs.seekg(0, std::ios::end);
        size_t fileSize = ifs.tellg();
        ifs.seekg(currentPos);
        return fileSize;
    }
    
    FunctionFromFile(const char* filePath)
    {
        load(filePath);
    }

    int operator()(int x) const
    {
        for (size_t i = 0; i < size; i++)
        {
            if (x == data[i])
            {
                return x;
            }
        }
        return 0;
    }
    
    bool good() const
    {
        return loaded;
    }

    FunctionFromFile(const FunctionFromFile& other) 
    {
        copyFrom(other);
    }

    FunctionFromFile& operator=(const FunctionFromFile& other) 
    {
        if (this != &other)
        {
            free();
            copyFrom(other);
        }
        return *this;
    }

    ~FunctionFromFile()
    {
        free();
    }
    
private:
    int* data = nullptr;
    size_t size = 0;
    bool loaded = false;

    void load(const char* filePath)
    {
        std::ifstream ifs(filePath, std::ios::binary);
        if (!ifs.is_open())
        {
            return;
        }
        
        loaded = true;
        size = getFileSize(ifs);
        data = new int[size];
        ifs.read(reinterpret_cast<char*>(data), size * sizeof(int));
    }

    void copyFrom(const FunctionFromFile& other)
    {
        size = other.size;
        data = new int[size]{};
        for (size_t i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }

    void free()
    {
        delete[] data;
    }
};