#include <fstream>
#include <iostream>
#include <cstring>
#include <new>
#include <cstddef>
using std::cout;
using std::cin;
using std::endl;

#define FC_LEN 10

struct Student {
    char* name;
    unsigned short age;
    char facultyNumber[FC_LEN + 1];
};

bool writeStudentToFile(const Student& student, std::ofstream& file) {
    size_t nameLen = strlen(student.name);
    file.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    file.write(student.name, nameLen);
    file.write(reinterpret_cast<const char*>(&student.age), sizeof(student.age));
    file.write(student.facultyNumber, FC_LEN);
    if (!file) {
        cout << "Writing failed!" << endl;
        return false;
    }
    return true;
}

bool writeStudentsToFile(const Student* students, const size_t studentsCount, std::ofstream& file) {
    file.write(reinterpret_cast<const char*>(&studentsCount), sizeof(studentsCount));
    if (!file) {
        cout << "Writing failed!" << endl;
        return false;
    }
    for (size_t i = 0; i < studentsCount; i++) {
        if (!writeStudentToFile(students[i], file)) {
            return false;
        }
    }
    return true;
}

bool readStudentFromFile(Student& student, std::ifstream& file) {
    size_t nameLen;
    file.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    char* name = new(std::nothrow) char[nameLen + 1];
    if (name == nullptr) {
        cout << "Memory allocation failed!" << endl;
        file.close();
        return false;
    }
    file.read(name, nameLen);
    name[nameLen] = '\0';
    file.read(reinterpret_cast<char*>(&student.age), sizeof(student.age));
    file.read(student.facultyNumber, FC_LEN);
    if (!file.good()) {
        cout << "Reading failed!" << endl;
        return false;
    }
    student.name = name;
    return true;
}

size_t readStudentsCount(std::ifstream& file) {
    size_t readStudentsCount;
    file.read(reinterpret_cast<char*>(&readStudentsCount), sizeof(readStudentsCount));
    if (!file.good()) {
        cout << "Reading failed!" << endl;
        return 0;
    }
    return readStudentsCount;
}

bool readStudentsToFile(Student* students, const size_t studentsCount, std::ifstream& file) {
    if (!file.good()) {
        cout << "Reading failed!" << endl;
        return false;
    }
    for (size_t i = 0; i < studentsCount; i++) {
        if (!readStudentFromFile(students[i], file)) {
            return false;
        }
    }

    return true;
}


int main() {
    const Student student1 = {"First", 21, "FACNUM1111"};
    const Student student2 = {"Second", 22, "FACNUM2222"};
    const Student student3 = {"Third", 23, "FACNUM3333"};
    Student students[] = {student1, student2, student3};

    std::ofstream oFile("students.bin", std::ios::binary | std::ios::trunc);
    if (!oFile.is_open()) {
        cout << "File can't be opened!";
        return -1;
    }
    if (!writeStudentsToFile(students, 3, oFile)) {
        oFile.close();
        cout << "Writing failed!";
        return -1;
    }
    oFile.close();

    std::ifstream iFile("students.bin", std::ios::binary);
    if (!iFile.is_open()) {
        cout << "File can't be opened!";
        return -1;
    }

    const size_t studentsCount = readStudentsCount(iFile);
    Student* readStudents = new(std::nothrow) Student[studentsCount];
    if (readStudents == nullptr) {
        cout << "Memory allocation failed!";
        iFile.close();
        return -1;
    }
    if (!readStudentsToFile(readStudents, studentsCount, iFile)) {
        iFile.close();
        cout << "Reading failed!";
        return -1;
    }
    iFile.close();

    for (size_t i = 0; i < studentsCount; i++) {
        cout << readStudents[i].name << " " << readStudents[i].age << " " << readStudents[i].facultyNumber << endl;
    }

    return 0;
}
