#include <iostream>
#include <fstream>

struct HexFile
{
  unsigned char *data;
  std::string filePath;
  size_t size;
  size_t capacity;
};

bool isValidPrintableAsciiSymbol(const unsigned char symbol)
{
  return symbol >= 'a' && symbol <= 'z' ||
         symbol >= 'A' && symbol <= 'Z' ||
         symbol >= '0' && symbol <= '9';
}

size_t getFileSize(std::ifstream &file)
{
  std::streampos currentPosition = file.tellg();

  file.seekg(0, std::ios::end);
  std::streampos fileSize = file.tellg();

  file.seekg(currentPosition);

  return fileSize;
}

bool getByteFromInput(unsigned char &byte)
{
  int inputVal;

  std::cout << "Enter a hex byte to add (00-FF): ";

  std::cin >> std::hex >> inputVal;
  std::cin >> std::dec;

  if (inputVal < 0 || inputVal > 255)
  {
    std::cerr << "Input value is out of range!" << std::endl;

    return false;
  }

  byte = static_cast<unsigned char>(inputVal);

  return true;
}

void addByteToHexFile(HexFile &file, const unsigned char byte)
{
  if (file.size >= file.capacity)
  {
    size_t newCapacity = (file.capacity == 0) ? 8 : file.capacity * 2;
    unsigned char *newData = new (std::nothrow) unsigned char[newCapacity];

    if (newData == nullptr)
    {
      std::cerr << "Memory allocation failed!" << std::endl;

      return;
    }

    if (file.data != nullptr)
    {
      for (size_t i = 0; i < file.size; i++)
      {
        newData[i] = file.data[i];
      }

      delete[] file.data;
    }

    file.data = newData;
    file.capacity = newCapacity;
  }

  file.data[file.size] = byte;
  file.size += 1;
}

void editByteInHexFile(HexFile &file, const size_t index, const unsigned char newByte)
{
  if (index >= file.size)
  {
    std::cerr << "Index out of bounds!" << std::endl;

    return;
  }

  file.data[index] = newByte;
}

void saveHexFile(const HexFile &file, const std::string &outputPath)
{
  std::ofstream outputFile(outputPath, std::ios::binary);

  if (!outputFile)
  {
    std::cerr << "Failed to save file: " << outputPath << std::endl;

    return;
  }

  outputFile.write(reinterpret_cast<const char *>(file.data), file.size);
  outputFile.close();
}

void printHexFile(const HexFile &file)
{
  std::string ascii_chars = "";

  for (size_t i = 0; i < file.size; i++)
  {
    unsigned char byte = file.data[i];

    if (byte < 16)
    {
      std::cout << '0';
    }
    std::cout << std::hex << static_cast<int>(byte) << ' ';

    ascii_chars += isValidPrintableAsciiSymbol(byte) ? byte : '.';
    ascii_chars += ' ';
  }

  std::cout << std::dec << std::endl;

  std::cout << ascii_chars << std::endl;
}

HexFile loadHexFile(const std::string &filePath)
{
  HexFile viewer = {nullptr, filePath, 0, 0};

  std::ifstream inputFile(filePath, std::ios::binary);

  if (!inputFile)
  {
    std::cerr << "Failed to open file: " << filePath << std::endl;

    return viewer;
  }

  size_t fileSize = getFileSize(inputFile);
  size_t capacity = fileSize * 2;

  viewer.data = new (std::nothrow) unsigned char[capacity];

  if (viewer.data == nullptr)
  {
    std::cerr << "Memory allocation failed!" << std::endl;

    return viewer;
  }

  viewer.size = fileSize;
  viewer.capacity = capacity;

  inputFile.read(reinterpret_cast<char *>(viewer.data), fileSize);
  inputFile.close();

  return viewer;
}

void freeHexFile(HexFile &viewer)
{
  delete[] viewer.data;
  viewer.data = nullptr;
  viewer.filePath = "";
  viewer.size = 0;
  viewer.capacity = 0;
}

int main()
{
  std::string filePath;
  std::cout << "Enter the path of the file to load (or 'exit' to quit): ";
  std::cin >> filePath;

  if (filePath == "exit")
  {
    return 0;
  }

  HexFile viewer = loadHexFile(filePath);

  if (viewer.data == nullptr)
  {
    return -1;
  }

  std::string option;
  while (true)
  {
    std::cout << "Choose between 'view', 'add', 'edit', 'save', 'save-as' or 'exit': ";
    std::cin >> option;

    if (option == "view")
    {
      printHexFile(viewer);

      continue;
    }

    if (option == "add")
    {
      unsigned char byte;

      if (getByteFromInput(byte))
      {
        addByteToHexFile(viewer, byte);
      }

      continue;
    }

    if (option == "edit")
    {
      size_t index;

      std::cout << "Enter the index of the byte to edit: ";
      std::cin >> index;

      unsigned char byte;

      if (getByteFromInput(byte))
      {
        editByteInHexFile(viewer, index, byte);
      }

      continue;
    }

    if (option == "save")
    {
      saveHexFile(viewer, viewer.filePath);

      continue;
    }

    if (option == "save-as")
    {
      std::string newFilePath;
      std::cout << "Enter the new file path: ";
      std::cin >> newFilePath;

      saveHexFile(viewer, newFilePath);

      continue;
    }

    if (option == "exit")
    {
      break;
    }
  }

  freeHexFile(viewer);

  return 0;
}
