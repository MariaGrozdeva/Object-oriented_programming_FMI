#include <iostream>
#include <cstring>
#include <fstream>
 
#define SPECIALITY_POSITION 4
#define MAX_SIZE 1024
#define FN_SIZE 10
#define MAX_SIZE1 32
 
enum class Speciality
{
    INFORMATICS,
    SOFTWARE_ENGINEERING,
    INFORMATION_SYSTEMS,
    COMPUTER_SCIENCE
};
 
struct Student
{
    char firstName[MAX_SIZE1];
    char lastName[MAX_SIZE1];
    char email[MAX_SIZE1];
    char fn[FN_SIZE];
    Speciality subject;
};
 
struct StudentsCollection
{
    Student *arr;
};
 
int getCntOfStudents(std::ifstream& file)
{
    char line[MAX_SIZE];
    int cntOfStudents = 0;
    while(!file.eof())
    {
        file.getline(line, MAX_SIZE);
        ++cntOfStudents;
    }
 
    file.seekg(0, std::ios::beg);
    return --cntOfStudents;
}
 
void findSpeciality(Student& student)
{
    switch(student.fn[SPECIALITY_POSITION])
    {
        case '4': student.subject = Speciality::INFORMATICS; break;
        case '6': student.subject = Speciality::SOFTWARE_ENGINEERING; break;
        case '7': student.subject = Speciality::INFORMATION_SYSTEMS; break;
        case '8': student.subject = Speciality::COMPUTER_SCIENCE; break;
        default: std::cerr << "Invalid FN!"; exit(-1);
    }
}
 
void dataCollection(const char*& source, char* destination)
{
    while(!(*source == ',' || *source == '\0'))
    {
        *destination = *source;
        ++source;
        ++destination;
    }
 
    ++source;
    *destination = '\0';
}
 
void initializeStudent(Student& student, const char* str)
{
    dataCollection(str, student.firstName);
    dataCollection(str, student.lastName);
    dataCollection(str, student.email);
    dataCollection(str, student.fn);
 
    findSpeciality(student);
}
 
int fillStudentArr(StudentsCollection& obj)
{
    std::ifstream file("students");
    if(!file.is_open())
    {
        std::cerr << "Can not be opened!" << '\n';
        exit(-1);
    }
 
    int cnt = getCntOfStudents(file);
    obj.arr = new Student[cnt];
 
    char str[MAX_SIZE];
    file.getline(str, MAX_SIZE);
    for(int i = 0; i < cnt; ++i)
    {
        file.getline(str, MAX_SIZE);
        initializeStudent(obj.arr[i], str);
    }
 
    file.close();
    return cnt;
}
 
void printAll(const StudentsCollection& obj, int cnt)
{
    for(int i = 0; i < cnt; ++i)
    {
        std::cout << obj.arr[i].firstName << ',' << obj.arr[i].lastName << ',' << obj.arr[i].email << ',' << obj.arr[i].fn << ',';
 
        switch(obj.arr[i].fn[SPECIALITY_POSITION])
            {
                case '4': std::cout << "Informatics"; break;
                case '6': std::cout << "Software engineering"; break;
                case '7': std::cout << "Information systems"; break;
                case '8': std::cout << "Computer science"; break;
            }
        std::cout << "\n\n";
    }
}
 
void searchByFN(const StudentsCollection& obj, const char* fn, int cnt)
{
    if(strlen(fn) > FN_SIZE)
    {
        std::cerr << "Invalid FN!";
        exit(-1);
    }
 
    for(int i = 0; i < cnt; ++i)
    {
        if(strcmp(obj.arr[i].fn, fn) == 0)
        {
            std::cout << "Names: " << obj.arr[i].firstName << ", " << obj.arr[i].lastName <<
                "\nEmail: " << obj.arr[i].email << "\nFn: " << obj.arr[i].fn << "\nSpeciality: ";
 
            switch(obj.arr[i].fn[SPECIALITY_POSITION])
            {
                case '4': std::cout << "Informatics"; break;
                case '6': std::cout << "Software engineering"; break;
                case '7': std::cout << "Information systems"; break;
                case '8': std::cout << "Computer science"; break;
            }
            return;
        }
    }
    std::cout << "There is no such student!";
 
}
 
void changeEmail(StudentsCollection& obj, const char* fn, const char* replaceWith, int cnt) //not constant cuz we want to change the email
{
    bool flag = false;
    for(int i = 0; i < cnt; ++i)
    {
        if(strcmp(obj.arr[i].fn, fn) == 0)
        {
            flag = true;
            strcpy(obj.arr[i].email, replaceWith);
        }
    }
    if(!flag)
    {
        std::cerr << "Ivalid FN!";
        exit(-1);
    }
}
 
void writeInFile(const StudentsCollection& obj, int cnt)
{
    std::ofstream file("newFile");
    if(!file.is_open())
    {
        std::cerr << "Can not be opened!" << '\n';
        exit(-1);
    }
 
    for(int i = 0; i < cnt; ++i)
    {
        file << obj.arr[i].firstName << ',' << obj.arr[i].lastName << ',' << obj.arr[i].email << ',' << obj.arr[i].fn << std::endl;
    }
 
    file.close();
}
 
int main()
{
    StudentsCollection obj;
    int cnt = fillStudentArr(obj);
 
    bool isValid = true;
    do
    {
        int operation;
        std::cout << "Chose one of the operations: \n1 - change email \n2 - write in file \n3 - search student by faculty number \n4 - show all students \n0 - exit\n";
        std::cin >> operation;
        std::cout << '\n';
        if(operation == 1)
        {
            char facNum[FN_SIZE];
            std::cout << "Enter the faculty number: ";
            std::cin >> facNum;
            char email[MAX_SIZE1];
            std::cout << "Enter the new email: ";
            std::cin >> email;
            changeEmail(obj, facNum, email, cnt);
        }
        else if(operation == 2)
        {
            writeInFile(obj, cnt);
        }
        else if(operation == 3)
        {
            char facNum[MAX_SIZE1];
            std::cout << "Enter the faculty number: ";
            std::cin >> facNum;
            searchByFN(obj, facNum, cnt);
        }
        else if(operation == 4)
        {
            printAll(obj, cnt);
        }
        else
        {
            if(operation != 0)
            {
                std::cout << "Invalid operation!";
            }
            isValid = false;
        }
 
        std::cout << "\n\n";
        system("pause");
        system("CLS");
    }while(isValid);
 
    delete[] obj.arr;
}
