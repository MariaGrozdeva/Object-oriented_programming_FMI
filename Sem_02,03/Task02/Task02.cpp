#include <iostream>
#include <fstream>

#pragma warning (disable : 4996)

const unsigned MAX_SIZE = 1024;
const unsigned specialityDigitPos = 4;

enum class Speciality // safer than plain enum!
{
	Informatics,
	ComputerScience,
	SoftwareEngineering
};

struct Student
{
	Speciality spec;

	char firstName[MAX_SIZE];
	char lastName[MAX_SIZE];
	char email[MAX_SIZE];
	char fn[MAX_SIZE];
};
struct StudentsCollection
{
	Student* data;
};

int getStudentsCount(const char* fileName, std::ifstream& file)
{
	char buff[MAX_SIZE];
	size_t studentsCount = 0;
	while (!file.eof())
	{
		file.getline(buff, MAX_SIZE);
		studentsCount++;
	}

	file.close();
	return studentsCount - 1;
}

void parseField(const char*& source, char* dest)
{
	while (*source != ',' && *source != '\0')
	{
		*dest = *source;
		source++;
		dest++;
	}

	source++;
	*dest = '\0';
}
void setSpeciality(Student& student)
{
	if (student.fn[specialityDigitPos] == '2')
		student.spec = Speciality::Informatics;
	else if (student.fn[specialityDigitPos] == '8')
		student.spec = Speciality::ComputerScience;
	else
		student.spec = Speciality::SoftwareEngineering;
}
void initialiseStudent(Student& student, const char* line)
{
	parseField(line, student.firstName);
	parseField(line, student.lastName);
	parseField(line, student.email);
	parseField(line, student.fn);

	setSpeciality(student);
}

int fillStudentsCollection(const char* fileName, StudentsCollection& collection)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "File can't be opened!" << std::endl;
		return -1;
	}

	int studentsCount = getStudentsCount(fileName, file);
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
			if (collection.data[i].fn[specialityDigitPos] == '2')
				std::cout << "Speciality: Informatics" << std::endl;
			else if (collection.data[i].fn[specialityDigitPos] == '8')
				std::cout << "Speciality: Computer science" << std::endl;
			else
				std::cout << "Speciality: Software engineering" << std::endl;
		}
	}
}
void changeEmail(const StudentsCollection& collection, const char* fn, const char* newEmail, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(collection.data[i].fn, fn) == 0)
			strcpy(collection.data[i].email, newEmail);
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
		saveStudent(collection.data[i], file);

	file.close();
}

int main()
{
	std::cout << "Open file: ";
	char fileName[MAX_SIZE];
	std::cin >> fileName;

	StudentsCollection collection;
	size_t size = fillStudentsCollection(fileName, collection);
	if (size == -1)
		return -1;

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