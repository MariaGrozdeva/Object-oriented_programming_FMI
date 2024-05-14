#include <iostream>
#include "FilePath.h"
#include "BinaryFileReader.h"
#include "BinaryFileWriter.h"
#include "CSVFileReader.h"
#include "CSVFileWriter.h"
#include "ArrFileReader.h"
#include "ArrFileWriter.h"

FileReader* getFileReader(const MyString& filePath)
{
    FilePath path(filePath);

    if (path.getExtension() == ".dat")
    {
        return new BinaryFileReader(filePath);
    }
    if (path.getExtension() == ".csv")
    {
        return new CSVFileReader(filePath);
    }
    if (path.getExtension() == ".arr")
    {
        return new ArrFileReader(filePath);
    }

    throw std::invalid_argument("Invalid file extension");
}

FileWriter* getFileWriter(const MyString& filePath)
{
    FilePath path(filePath);

    if (path.getExtension() == ".dat")
    {
        return new BinaryFileWriter(filePath);
    }
    if (path.getExtension() == ".csv")
    {
        return new CSVFileWriter(filePath);
    }
    if (path.getExtension() == ".arr")
    {
        return new ArrFileWriter(filePath);
    }

    throw std::invalid_argument("Invalid file extension");
}

void selectionSort(int* arr, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        int minElIndex = i;
        for (size_t j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minElIndex])
            {
                minElIndex = j;
            }
        }

        if (minElIndex != i)
        {
            std::swap(arr[minElIndex], arr[i]);
        }
    }
}


void transfer(const MyString& inFile, const MyString& outFile)
{
    int* arr = nullptr;
    size_t size;

    FileReader* reader = getFileReader(inFile);
    reader->read(arr, size);
    selectionSort(arr, size);

    FileWriter* writer = getFileWriter(outFile);
    writer->write(arr, size);
    delete[] arr;
}

int main()
{
    transfer("numbers.dat", "numbers2.arr");
}
