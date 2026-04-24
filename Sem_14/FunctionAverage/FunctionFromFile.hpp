#include <fstream>

class FunctionFromFile
{
public:
    static size_t getFileSize(std::ifstream& ifs)
    {
        std::streampos currentPos = ifs.tellg();
        ifs.seekg(0, std::ios::end);
        size_t fileSize = ifs.tellg();
        ifs.seekg(currentPos, std::ios::beg);
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
    
    FunctionFromFile(const FunctionFromFile& other) : data(nullptr), size(0), loaded(other.loaded)
    {
        data = new int[other.size];
        for (size_t i = 0; i < other.size; i++)
        {
            data[i] = other.data[i];
        }
        size = other.size;
    }
    
    FunctionFromFile& operator=(const FunctionFromFile& other) 
    {
        if (this != &other)
        {
            int* newData = new int[other.size];
            for (size_t i = 0; i < other.size; i++)
            {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
            size = other.size;
            loaded = other.loaded;
        }
        return *this;
    }
    
    ~FunctionFromFile()
    {
        delete[] data;
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
        
        size = getFileSize(ifs) / sizeof(int);
        data = new int[size];
        if (ifs.read(reinterpret_cast<char*>(data), size * sizeof(int)))
        {
            loaded = true;
        }
    }
};
