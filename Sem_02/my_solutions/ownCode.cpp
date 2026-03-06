#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("ownCode.cpp");
    if (!file.is_open()) {
        std::cout << "File can't be opened!";
        return -1;
    }

    constexpr int BUFF_SIZE = 1024;
    char buff[BUFF_SIZE];

    while (!file.eof()) {
        file.getline(buff, BUFF_SIZE);
        std::cout << buff << "\n";
    }
    
    file.close();
    return 0;
}