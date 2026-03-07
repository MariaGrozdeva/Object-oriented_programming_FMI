#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning (disable : 4996)

const size_t MAX_SIZE = 1024;
const unsigned SPEC_DIGIT_POS = 4;

enum class Major
{
	Informatics = 4,
	ComputerScience = 8,
	SoftwareEngineering = 6,
	InformationSystems = 7
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
};

unsigned int getStudentsCount(std::ifstream& file)
{
	char buff[MAX_SIZE];
	unsigned int studentsCount = 0;

	while (file.getline(buff, MAX_SIZE))
	{
		studentsCount++;
	}

	file.clear();
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

	if (*src == ',')
	{
		src++;
	}
	*dest = '\0';
}

void setMajor(Student& student)
{
	const int majorDigit = student.fn[SPEC_DIGIT_POS] - '0';

	if (majorDigit == (int)Major::Informatics)
	{
		student.major = Major::Informatics;
	}
	else if (majorDigit == (int)Major::ComputerScience)
	{
		student.major = Major::ComputerScience;
	}
	else if (majorDigit == (int)Major::SoftwareEngineering)
	{
		student.major = Major::SoftwareEngineering;
	}
	else if (majorDigit == (int)Major::InformationSystems)
	{
		student.major = Major::InformationSystems;
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

int fillStudentsCollection(StudentsCollection& collection, const char* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "File can't be opened!" << std::endl;
		return -1;
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
	return studentsCount;
}

void printByFn(const StudentsCollection& collection, const char* fn, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(collection.data[i].fn, fn) == 0)
		{
			std::cout << "Name: " << collection.data[i].firstName << ' ' << collection.data[i].lastName <<
				", Email: " << collection.data[i].email << ", FN: " << collection.data[i].fn << std::endl;
			if (collection.data[i].major == Major::Informatics)
			{
				std::cout << "Major: Informatics" << std::endl;
			}
			else if (collection.data[i].major == Major::ComputerScience)
			{
				std::cout << "Major: Computer science" << std::endl;
			}
			else if (collection.data[i].major == Major::SoftwareEngineering)
			{
				std::cout << "Major: Software engineering" << std::endl;
			}
			else if (collection.data[i].major == Major::InformationSystems)
			{
				std::cout << "Major: Information systems" << std::endl;
			}
		}
	}
}

void changeEmail(StudentsCollection& collection, const char* fn, const char* newEmail, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(collection.data[i].fn, fn) == 0)
		{
			strcpy(collection.data[i].email, newEmail);
			return; // fn is unique
		}
	}
}

void saveStudent(const Student& student, std::ofstream& file)
{
	file << student.firstName << ',' << student.lastName << ',' << student.email << ',' << student.fn << std::endl;
}

void save(const StudentsCollection& collection, const char* fileName, size_t size)
{
	std::ofstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "File can't be opened!" << std::endl;
		return;
	}

	char firstLine[MAX_SIZE] = "First name,Last name,Email address,FN\n";
	file << firstLine;

	for (size_t i = 0; i < size; i++)
	{
		saveStudent(collection.data[i], file);
	}

	file.close();
}

int main()
{
	std::cout << "Open file: ";
	char fileName[MAX_SIZE];
	std::cin >> fileName;

	StudentsCollection collection;
	int size = fillStudentsCollection(collection, fileName);
	if (size == -1)
	{
		return -1;
	}

	std::cout << "File successfully opened!" << std::endl << std::endl;

	char command[MAX_SIZE];
	do
	{
		std::cin >> command;

		if (strcmp(command, "print") == 0)
		{
			char fn[MAX_SIZE];
			std::cin >> fn;

			printByFn(collection, fn, size);
			std::cout << std::endl;
		}

		else if (strcmp(command, "edit") == 0)
		{
			char fn[MAX_SIZE], newEmail[MAX_SIZE];
			std::cin >> fn >> newEmail;

			changeEmail(collection, fn, newEmail, size);
			std::cout << std::endl;
		}

		else if (strcmp(command, "save") == 0)
		{
			char fileName[MAX_SIZE];
			std::cin >> fileName;

			save(collection, fileName, size);
			std::cout << "File " << fileName << " successfully saved!" << std::endl << std::endl;
		}
	} while (strcmp(command, "exit") != 0);

	delete[] collection.data;
}
