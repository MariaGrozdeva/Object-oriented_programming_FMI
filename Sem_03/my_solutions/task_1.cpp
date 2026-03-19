#include <fstream>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

size_t getFileSize(std::ifstream& file) {
    const std::streampos currentPos = file.tellg();
    file.seekg(0, std::ios::end);
    const size_t fileSize = static_cast<size_t>(file.tellg());
    file.seekg(currentPos);
    return fileSize;
}

int main() {
    int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::ofstream oFile("file.bin", std::ios::binary | std::ios::trunc);
    if (!oFile.is_open()) {
        cout << "File can't be opened!\n";
        return -1;
    }
    oFile.write(reinterpret_cast<const char*>(numbers), sizeof(numbers));
    if (!oFile) {
        cout << "Writing failed!\n";
        oFile.close();
        return -1;
    }
    oFile.close();
    cout << "Writing successful!" << endl;

    std::ifstream iFile("file.bin", std::ios::binary);
    if (!iFile.is_open()) {
        cout << "File can't be opened!\n";
        return -1;
    }

    const size_t fileSize = getFileSize(iFile);
    const size_t elementsCount = fileSize / sizeof(int);
    int* readNumbers = new(std::nothrow) int[elementsCount];
    if (readNumbers == nullptr) {
        cout << "Memory allocation failed!\n";
        iFile.close();
        return -1;
    }

    iFile.read(reinterpret_cast<char*>(readNumbers), fileSize);
    if (!iFile) {
        cout << "Reading failed!\n";
        iFile.close();
        return 0;
    }
    iFile.close();

    for (int i = 0; i < elementsCount; i++) {
        cout << readNumbers[i] << " ";
    }

    return 0;
}
