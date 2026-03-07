#include <iostream>
#include <fstream>

enum class Мajor
{
	CS,
    	I,
    	SE,
    	IS
};

struct Student
{
	char name[32];
	int age;
	Мajor major;
};

void saveStudentToFile(std::ofstream& ofs, const Student& st)
{
	ofs << st.name << std::endl;
	ofs << st.age << std::endl;
	ofs << static_cast<int>(st.major) << std::endl;
}

void readStudentFromFile(std::ifstream& ifs, Student& st)
{
	ifs.getline(st.name, 32);
	ifs >> st.age;
	ifs.ignore(); // ignore the \n
	int majorInt;
	ifs >> majorInt;
	st.major = static_cast<Мajor>(majorInt);
	ifs.ignore(); // ignore the \n
}

void writeArrayToFile(const char* fileName, const Student* students, const size_t size)
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		return;
	}
	
	ofs << size << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		saveStudentToFile(ofs, students[i]);
	}
	ofs.close();
}

Student* readArrayFromFile(const char* fileName, size_t& size)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		return nullptr;
	}
	
	ifs >> size;
	ifs.ignore();
	Student* result = new Student[size];

	for (size_t i = 0; i < size; i++)
	{
		readStudentFromFile(ifs, result[i]);
	}
	ifs.close();
	return result;
}

int main()
{
	Student students[] = { {"Galya", 34, Мajor::CS}, { "Georgi", 35, Мajor::I } };

	writeArrayToFile("students.txt", students, 2);
	size_t size;
	Student* result = readArrayFromFile("students.txt", size);
	for (size_t i = 0; i < size; i++)
	{
		std::cout << result[i].name << " " << result[i].age <<" " << (int)result[i].major << std::endl;
	}
	
	delete[] result;
}
