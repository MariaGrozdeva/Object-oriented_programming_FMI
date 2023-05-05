#include <iostream>
#include <fstream>

const unsigned int MAX_LENGTH = 128;
const unsigned int FN_LENGTH = 11;
const unsigned int BUFF_LENGTH = 1024;
const char* FIRST_LINE = "First name,Last name,Email address,FN\n";

struct Student
{
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char email[MAX_LENGTH];
    char fn[FN_LENGTH];
};

struct Students
{
    Student* data = nullptr;
    unsigned int studentsCount = 0;
};

int getStudentsCount(std::ifstream& file)
{
    // if there is '\n' at the end of the file the application doesn't work
    char buff[BUFF_LENGTH];
    int counter = 0;
    while (!file.eof())
    {
        file.getline(buff, BUFF_LENGTH);
        counter++;
    }
    file.seekg(0, std::ios::beg);

    return counter - 1;
}

void parseField(char* field, const char*& line)
{
    // ',' and ';' because some csv files use semicolon as delimiter
    while ((*line != ',' && *line != ';') && *line != '\0')
    {
        *field = *line;
        field++;
        line++;
    }
    *field = '\0';
    line++;
}

void initStudent(Student& student, const char* line)
{
    parseField(student.firstName, line);
    parseField(student.lastName, line);
    parseField(student.email, line);
    parseField(student.fn, line);
}

int readFile(Students& collection, const char* fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Error!" << std::endl;
        return -1;
    }

    int studentsCount = getStudentsCount(file);
    if (studentsCount < 1)
    {
        std::cout << "Empty file!" << std::endl;
        return -1;
    }
    collection.studentsCount = studentsCount;

    char buff[BUFF_LENGTH];
    collection.data = new Student[studentsCount];
    file.getline(buff, BUFF_LENGTH);
    for (int i = 0; i < studentsCount; ++i)
    {
        file.getline(buff, BUFF_LENGTH);
        initStudent(collection.data[i], buff);
    }

    file.close();
    return 0;
}

int getStudentInd(const Students& collection, const char* fn, unsigned int studentsCount)
{
    for (int i = 0; i < studentsCount; ++i)
    {
        if (strcmp(collection.data[i].fn, fn) == 0)
        {
            return i;
        }
    }
    return -1;
}

void printStudentByFN(const Students& collection, const char* fn)
{
    int studentInd = getStudentInd(collection, fn, collection.studentsCount);
    if (studentInd == -1)
    {
        std::cout << "There is no such student!" << std::endl;
        return;
    }

    std::cout << collection.data[studentInd].firstName << ' ' << collection.data[studentInd].lastName << '\n';
    std::cout << collection.data[studentInd].email << '\n';
    std::cout << collection.data[studentInd].fn << '\n';
    std::cout << std::endl;
}

// helper function
void printStudents(const Students& collection, int studentsCount)
{
    for (int i = 0; i < studentsCount; ++i)
    {
        printStudentByFN(collection, collection.data[i].fn);
    }
    std::cout << std::endl;
}

void changeStudentEmail(Students& collection, const char* fn, const char* newEmail)
{
    int studentInd = getStudentInd(collection, fn, collection.studentsCount);
    if (studentInd == -1)
    {
        std::cout << "There is no such student!" << std::endl;
        return;
    }

    strcpy_s(collection.data[studentInd].email, MAX_LENGTH, newEmail);
}

int saveFile(const Students& collection, const char* fileName)
{
    std::ofstream file(fileName);
    if (!file)
    {
        std::cout << "Error!" << std::endl;
        return -1;
    }

    file << FIRST_LINE;
    for (int i = 0; i < collection.studentsCount; ++i)
    {
        // last student must not have '\n'
        if (i == collection.studentsCount - 1)
        {
            file << collection.data[i].firstName << ',' << collection.data[i].lastName << ','
                << collection.data[i].email << ',' << collection.data[i].fn;
            break;
        }
        file << collection.data[i].firstName << ',' << collection.data[i].lastName << ','
            << collection.data[i].email << ',' << collection.data[i].fn << '\n';
    }

    if (file.fail())
        return -1;

    file.close();
    return 0;
}

int main()
{
    std::cout << "Enter file name: " << std::endl;
    char fileName[MAX_LENGTH];
    std::cin >> fileName;

    Students collection;
    int result = readFile(collection, fileName);
    if (result == 0)
        std::cout << "File succesfully read!" << std::endl;
    else
        return -1;

    // test that file is read correctly
    //printStudents(collection, collection.studentsCount);

    char command[MAX_LENGTH];
    char str1[MAX_LENGTH];
    char str2[MAX_LENGTH];

    while (true)
    {
        std::cout << "Enter command: ";
        std::cin >> command;
        if (strcmp(command, "print") == 0)
        {
            std::cout << "Enter fn: ";
            std::cin >> str1;
            printStudentByFN(collection, str1);
        }
        else if (strcmp(command, "edit") == 0)
        {
            std::cout << "Enter new email: ";
            std::cin >> str1;
            std::cout << "Enter fn: ";
            std::cin >> str2;
            changeStudentEmail(collection, str2, str1);
        }
        else if (strcmp(command, "save") == 0)
        {
            std::cout << "Enter file name: ";
            std::cin >> str1;
            result = saveFile(collection, str1);
            if (result == 0)
            {
                std::cout << "File succesfully saved!" << std::endl;
                break;
            }
            else
                return -1;
        }
        else
            std::cout << "There is no such command!" << std::endl;
    }

    delete[] collection.data;
}