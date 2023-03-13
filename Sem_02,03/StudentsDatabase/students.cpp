#include <iostream>
#include <fstream>
#include <string.h>
const int BUFF_SIZE = 1024;
const int NAME_AND_EMAIL_SIZE = 128;
const int FN_SIZE = 11;
const int MAJ_DIGIT_POS = 4;
const int FUNCTION_SIZE = 6;
enum class Major{
    Informatics = 4,
	ComputerScience = 8,
	SoftwareEngineering = 6
};

struct Student{
    Major major;
    char firstName[NAME_AND_EMAIL_SIZE];
    char lastName[NAME_AND_EMAIL_SIZE];
    char email[NAME_AND_EMAIL_SIZE];
    char fn[FN_SIZE];
};
struct StudentDatabase{
    Student *data;
};
void setMajor(Student& student)
{
	if ((student.fn[MAJ_DIGIT_POS] - '0') == (int)Major::Informatics)
	{
		student.major = Major::Informatics;
	}
	else if ((student.fn[MAJ_DIGIT_POS] - '0') == (int)Major::ComputerScience)
	{
		student.major = Major::ComputerScience;
	}
	else if ((student.fn[MAJ_DIGIT_POS] - '0') == (int)Major::SoftwareEngineering)
	{
		student.major = Major::SoftwareEngineering;
	}
}
unsigned int getStudentsCount(const char *fileName){
    std::ifstream file(fileName);
    unsigned int studentsCount = 0;
    if(!file.is_open()){
        std::cout << "File is not open" << std::endl;
        return -1;
    }
    char buff[BUFF_SIZE];
    while(!file.eof()){
        file.getline(buff, BUFF_SIZE);
        studentsCount++;
    }
    file.seekg(0, std::ios::beg);
    file.close();
    return studentsCount - 1;
}
void parseField(char* dest, const char*& src) // Note to self: const char*& src has to take a const char * variable to work
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
void initialiseStudent(Student& student, const char *line){
    parseField(student.firstName, line);
    parseField(student.lastName, line);
    parseField(student.email, line);
    parseField(student.fn, line);

    setMajor(student);
}
int fillStudentDatabase(StudentDatabase& database, const char *fileName){
    std::ifstream file(fileName);
    if(!file.is_open()){
        std::cout << "File is not open" << std::endl;
        return -1;
    }
    unsigned int studentsCount = getStudentsCount(fileName);
	database.data = new Student[studentsCount];
    char buff[BUFF_SIZE];
    file.getline(buff, BUFF_SIZE);
    for(size_t i = 0; i < studentsCount; i++){
        file.getline(buff, BUFF_SIZE);
        initialiseStudent(database.data[i], buff);
    }
    file.close();
    return studentsCount;
}
void printByFn(const StudentDatabase& database, const char* fn, size_t studentsCount){
    for(size_t i = 0; i < studentsCount; i++){
        if(strcmp(database.data[i].fn, fn) == 0) 
        std::cout << "Name: " << database.data[i].firstName << " " << database.data[i].lastName << ", Email:" << database.data[i].email << ", FN:" << database.data[i].fn << std::endl; 
    }
}
void editEmailByFn(StudentDatabase& database, const char* fn, const char* newEmail, size_t studentsCount){
    for(size_t i = 0; i < studentsCount; i++){
        if(strcmp(database.data[i].fn, fn) == 0) 
        strcpy(database.data[i].email, newEmail); 
    }
}
int saveStundentsFile(const StudentDatabase& database, const char *fileName, size_t studentsCount){
    std::ofstream file(fileName);
    if(!file.is_open()){
        std::cout << "File could not be saved" << std::endl;
        return -1;
    }
    file << "First name,Last name,Email address,FN" << std::endl;
    for(size_t i = 0; i < studentsCount; i++){
        file << database.data[i].firstName << "," << database.data[i].lastName << ","
        << database.data[i].email << "," << database.data[i].fn << std::endl;
    }
    file.close();
}
void parseFunc(char* dest, const char*& src)
{
	while (*src != ' ' && *src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
	}

	src++;
	*dest = '\0';
}
void initialiseFunc(char *func, char *par1, char *par2, const char *line){
    parseFunc(func, line);
    parseFunc(par1, line);
    if(*line != '\0')
    parseFunc(par2, line);
    else *par2 = '\0';
}
int main(){
    char fileName[BUFF_SIZE];
    std::cout << "Open File:" << std::endl;
    std::cin.getline(fileName, BUFF_SIZE);
    std::cin.clear();
    int studentsCount = getStudentsCount(fileName);
    StudentDatabase database;
    fillStudentDatabase(database, fileName);
    char function[FUNCTION_SIZE];
    char par1[BUFF_SIZE];
    char par2[BUFF_SIZE];
    char buff[BUFF_SIZE];
    while(strcmp(buff, "exit") != 0){
        std::cin.getline(buff, BUFF_SIZE);
        initialiseFunc(function, par1, par2, buff);
        if(strcmp(function, "print") == 0){
            printByFn(database, par1, studentsCount);
        }
        if(strcmp(function, "edit") == 0){
            editEmailByFn(database, par1, par2, studentsCount);
        }
        if(strcmp(function, "save") == 0){
            saveStundentsFile(database, par1, studentsCount);
        }
    }
    delete[] database.data;
    return 0;
}
