#include <iostream>
#include <fstream>
#include <cstring>

const unsigned FN_SIZE = 10;

struct Student
{
	char* name;
	unsigned int age;
	char fn[FN_SIZE];
};

struct StudentsCollection
{
	Student* data;
};

void writeStudentsToFile(const StudentsCollection& collection, std::ofstream& oFile, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		size_t len = strlen(collection.data[i].name);
		oFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
		oFile.write(collection.data[i].name, len);
		oFile.write(reinterpret_cast<const char*>(&collection.data[i].age), sizeof(collection.data[i].age));
		oFile.write(collection.data[i].fn, sizeof(collection.data[i].fn));
	}
}

void readStudentsFromFile(StudentsCollection& collection, std::ifstream& iFile, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		size_t nameLen;
		iFile.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
		collection.data[i].name = new char[nameLen + 1];
		iFile.read(collection.data[i].name, nameLen);
		collection.data[i].name[nameLen] = '\0';

		iFile.read(reinterpret_cast<char*>(&collection.data[i].age), sizeof(collection.data[i].age));
		iFile.read(collection.data[i].fn, sizeof(collection.data[i].fn));
	}
}

int main()
{
	std::cout << "Enter number of students: ";
	unsigned int n;
	std::cin >> n;

	{ // Write students to file
		std::ofstream oFile("myFile.dat", std::ios::binary);
		if (!oFile.is_open())
		{
			std::cout << "File can't be opened!" << std::endl;
			return -1;
		}

		StudentsCollection collection;
		collection.data = new Student[n];

		std::cout << "Write the students by name, age and fn:" << std::endl << std::endl;
		for (size_t i = 0; i < n; i++)
		{
			std::cout << "Length of name of student " << i + 1 << ": ";
			size_t len;
			std::cin >> len;

			collection.data[i].name = new char[len + 1];
			std::cin >> collection.data[i].name;
			std::cin >> collection.data[i].age;
			std::cin >> collection.data[i].fn;
		}

		writeStudentsToFile(collection, oFile, n);

		for (size_t i = 0; i < n; i++)
		{
			delete[] collection.data[i].name;
		}
		delete[] collection.data;

		oFile.close();
	}

	{ // Read students from file
		std::ifstream iFile("myFile.dat", std::ios::binary);
		if (!iFile.is_open())
		{
			std::cout << "File can't be opened!" << std::endl;
			return -1;
		}

		StudentsCollection collection;
		collection.data = new Student[n];

		readStudentsFromFile(collection, iFile, n);

		for (size_t i = 0; i < n; i++)
		{
			std::cout << "Student" << ' ' << i << ":" << std::endl;
			std::cout << "Name: " << collection.data[i].name << ", Age: " << collection.data[i].age << ", FN: " << collection.data[i].fn << std::endl;
		}

		for (size_t i = 0; i < n; i++)
		{
			delete[] collection.data[i].name;
		}
		delete[] collection.data;

		iFile.close();
	}
}
