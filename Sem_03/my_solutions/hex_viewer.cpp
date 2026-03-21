#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <cstdlib>

void viewFile(std::fstream& file) {
    char byte;
    while (file.get(byte)) {
        const unsigned uByte = static_cast<unsigned char>(byte);
        std::cout << std::hex << std::setw(2) << std::setfill('0')<< static_cast<int>(uByte) << " ";
    }
    std::cout << std::endl;
    file.clear();
    file.seekg(0, std::ios::beg);
    while (file.get(byte)) {
        if ((byte >= 'A' && byte <= 'Z') || (byte >= 'a' && byte <= 'z')) {
            std::cout << byte << "  ";
        }
        else {
            std::cout << ".. ";
        }
    }
    std::cout << std::endl;
}

bool writeByteAt(std::fstream& file, const char* hexByte, std::streampos pos = 0) {
    file.seekp(pos, std::ios::beg);
    const unsigned long byte = strtoull(hexByte, nullptr, 16);
    const unsigned char uByte = static_cast<unsigned char>(byte);
    if (!file.put(static_cast<char>(uByte))) {
        return false;
    }
    return true;

}

size_t getFileSize(std::fstream& file) {
    const std::streampos currentPos = file.tellg();
    file.seekg(0, std::ios::end);
    const size_t fileSize = static_cast<size_t>(file.tellg());
    file.seekg(currentPos);
    return fileSize;
}

bool readHexByte(std::fstream& file, char* hexByte) {
    std::cin.getline(hexByte, 3);
    if (!std::cin) {
        std::cout << "Invalid input!";
        return false;
    }
    return true;
}

int main() {
    constexpr int x = 25409;
    constexpr short MAX_COMMAND_LEN = 100;
    constexpr int MAX_PATH_LEN = 1024;
    std::ofstream oFile("myData.bin", std::ios::binary);
    if (!oFile.is_open()) {
        std::cout << "File can't be opened!";
        return -1;
    }
    if (!oFile.write(reinterpret_cast<const char*>(&x), sizeof(x))) {
        std::cout << "Writing failed!";
        return -1;
    }
    oFile.close();

    char path[MAX_PATH_LEN];
    std::cout << "Enter the path to the file: ";
    std::cin.getline(path, MAX_PATH_LEN);
    if (!std::cin) {
        std::cout << "Invalid path!";
        return -1;
    }
    std::fstream file(path, std::ios::binary | std::ios::out | std::ios::in);
    if (!file.is_open()) {
        std::cout << "File can't be opened!";
        return -1;
    }

    const size_t fileSize = getFileSize(file);
    std::cout << "File loaded successfully. Size: " << fileSize << " bytes." << std::endl;

    char buff[MAX_COMMAND_LEN];
    while (true) {
        std::cin.getline(buff, MAX_COMMAND_LEN);
        if (!std::cin) {
            std::cout << "Invalid command!";
            file.close();
            return -1;
        }
        if (strcmp(buff, "view") == 0) {
            file.clear();
            file.seekg(0, std::ios::beg);
            viewFile(file);
        }
        else if (strcmp(buff, "add") == 0) {
            file.clear();
            file.seekp(0, std::ios::end);
            std::cout << "Enter hex byte to add: ";
            if (!readHexByte(file, buff)) {
                file.close();
                return -1;
            }

            if (!writeByteAt(file, buff, file.tellp())) {
                std::cout << "Writing failed!";
                file.close();
                return -1;
            }
            file.flush();
            std::cout << "Byte added successfully!" << std::endl;
        }
        else if (strcmp(buff, "change") == 0) {
            file.clear();
            unsigned pos = 0;
            std::cout << "Enter index: ";
            std:: cin >> pos;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter new hex byte: ";
            if (!readHexByte(file, buff)) {
                file.close();
                return -1;
            }
            if (!writeByteAt(file, buff, pos)) {
                std::cout << "Writing failed!";
                file.close();
                return -1;
            }

            std::cout << "Byte changed successfully!" << std::endl;
        }
        else if (strcmp(buff, "save as") == 0) {
            std::cout << "Enter new path: ";
            std::cin.getline(path, MAX_PATH_LEN);
            if (!std::cin) {
                std::cout << "Invalid path!";
            }

            std::ofstream newFile(path, std::ios::binary);
            if (!newFile.is_open()) {
                std::cout << "File can't be opened!";
                return -1;
            }

            file.clear();
            file.seekg(0, std::ios::beg);
            newFile << file.rdbuf();
            newFile.close();
            file.close();
            std::cout << "File saved successfully!" << std::endl;
            break;

        }
        else if (strcmp(buff, "save") == 0) {
            file.close();
            std::cout << "File saved successfully!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid command!";
        }

    }

    return 0;
}