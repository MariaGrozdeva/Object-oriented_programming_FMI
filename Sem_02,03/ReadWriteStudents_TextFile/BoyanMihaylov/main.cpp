#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

#pragma warning (disable : 4996)

const size_t MAX_SIZE = 1024;
const unsigned SPEC_DIGIT_POS = 4;

enum class Major
{
    Informatics = 4,
    ComputerScience = 8,
    SoftwareEngineering = 6
};

struct Student
{
    Major major;

    char firstName[MAX_SIZE];
    char lastName[MAX_SIZE];
    char email[MAX_SIZE];
    char fn[MAX_SIZE];
};
struct StudentsCollection
{
    Student* data;
    unsigned int size;
};

unsigned int getStudentsCount(std::ifstream& file)
{
    char buff[MAX_SIZE];
    unsigned int studentsCount = 0;

    while (!file.eof())
    {
        file.getline(buff, MAX_SIZE);
        studentsCount++;
    }

    file.seekg(0, std::ios::beg);
    return studentsCount - 1;
}

void parseField(char* dest, const char*& src)
{
    while (*src != ',' && *src != '\0')
    {
        *dest = *src;
        src++;
        dest++;
    }

    src++;
    *dest = '\0';
}

void setMajor(Student& student)
{
    if (student.fn[SPEC_DIGIT_POS] == (int)Major::Informatics)
    {
        student.major = Major::Informatics;
    }
    else if (student.fn[SPEC_DIGIT_POS] == (int)Major::ComputerScience)
    {
        student.major = Major::ComputerScience;
    }
    else if (student.fn[SPEC_DIGIT_POS] == (int)Major::SoftwareEngineering)
    {
        student.major = Major::SoftwareEngineering;
    }
}

void initialiseStudent(Student& student, const char* line)
{
    parseField(student.firstName, line);
    parseField(student.lastName, line);
    parseField(student.email, line);
    parseField(student.fn, line);

    setMajor(student);
}

void fillStudentsCollection(StudentsCollection& collection, const char* fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        collection.size = -1;
    }

    unsigned int studentsCount = getStudentsCount(file);
    collection.data = new Student[studentsCount];

    char buff[MAX_SIZE];
    file.getline(buff, MAX_SIZE);
    for (size_t i = 0; i < studentsCount; i++)
    {
        file.getline(buff, MAX_SIZE);
        initialiseStudent(collection.data[i], buff);
    }

    file.close();
    collection.size = studentsCount;
}

void printByFn(const StudentsCollection& collection, const char* fn)
{
    for (size_t i = 0; i < collection.size; i++)
    {
        if (strcmp(collection.data[i].fn, fn) == 0)
        {
            std::cout << "Name: " << collection.data[i].firstName << ' ' << collection.data[i].lastName <<
                      ", Email: " << collection.data[i].email << ", FN: " << collection.data[i].fn << std::endl;
            if (collection.data[i].fn[SPEC_DIGIT_POS] == (int)Major::Informatics)
            {
                std::cout << "Major: Informatics" << std::endl;
            }
            else if (collection.data[i].fn[SPEC_DIGIT_POS] == (int)Major::ComputerScience)
            {
                std::cout << "Major: Computer science" << std::endl;
            }
            else if (collection.data[i].fn[SPEC_DIGIT_POS] == (int)Major::SoftwareEngineering)
            {
                std::cout << "Major: Software engineering" << std::endl;
            }
        }
    }
}

void updateEmailByFN(StudentsCollection& collection, char newEmail[],char fn[]){
    bool end = false;
    for (int i = 0; i < collection.size && !end; ++i) {
        if(strcmp(collection.data[i].fn, fn) == 0){
            size_t len = strlen(newEmail) + 1;
            strcpy_s(collection.data[i].email,len, newEmail);
            end = true;
        }
    }
}

void saveToDisc(const StudentsCollection& collection, const char *filename) {
    std::ofstream file;
    char comma = ',';
    file.open(filename);
    file << "First name,Last name,Email address,FN" << std::endl;
    for (int i = 0; i < collection.size; ++i) {
        file << collection.data[i].firstName << comma
             << collection.data[i].lastName << comma
             << collection.data[i].email << comma
             << collection.data[i].fn << std::endl;
    }
    file.close();
}

bool commands(StudentsCollection& collection){ // We don't pass StudentsCollection as const reference, because we need to change the email string with 'edit' command.
    bool continueLoop = true;
    char command[MAX_SIZE];
    std::cout << "> ";
    std::cin >> command;

    if(strcmp(command, "help") == 0){
        std::cout  << std::left << std::setw(50)
                   << "help" << "Prints this help command." << std::endl
                   << std::left << std::setw(50)
                   << "print [Faculty Number]" << "Prints student information by their faculty number." << std::endl
                   << std::left << std::setw(50)
                   << "edit [Faculty Number] [New Email]"  << "Changes student's email by their faculty number." << std::endl
                   << std::left << std::setw(50)
                   << "save [Filename]" << "Saves changes to new file." << std::endl
                   << std::left << std::setw(50)
                   << "exit" << "Program Exits." << std::endl;
    }
    else if (strcmp(command, "print") == 0){
        char fn[MAX_SIZE];
        std::cin >> fn;

        printByFn(collection, fn);
        std::cout << std::endl;
    }
    else if(strcmp(command, "edit") == 0){
        char fn[MAX_SIZE];
        char newEmail[MAX_SIZE];
        std::cin >> fn >> newEmail;
        updateEmailByFN(collection, newEmail, fn);
    }
    else if(strcmp(command, "save") == 0){
        char newFilename[MAX_SIZE];
        std::cin >> newFilename;
        saveToDisc(collection, newFilename);
        //std::cout << "Here:" << newFilename << collection.data[0].email << std::endl;
    }


    else if(strcmp(command, "exit") == 0){
        continueLoop = false;
        return continueLoop;
    }
    return continueLoop;
}

int main()
{
    std::cout << "Open file: ";
    char fileName[MAX_SIZE];
    std::cin >> fileName;

    //char fileName[] = "students.csv";

    StudentsCollection collection;
    fillStudentsCollection(collection, fileName);
    if (collection.size == -1)
    {
        return -1;
    }
    std::cout << "File successfully opened!" << std::endl << std::endl;
    std::cout << "Enter help to list commands." << std::endl;
    while (commands(collection)){}
    delete[] collection.data;
}