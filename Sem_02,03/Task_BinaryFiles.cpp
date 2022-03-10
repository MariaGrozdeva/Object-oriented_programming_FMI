#include <iostream>
#include <fstream>

const unsigned FN_SIZE = 10;

struct Student
{
	char* name;
	size_t age;
	char fn[FN_SIZE];
};
struct StudentsCollection
{
	Student* data;
};

void writeStudentsToFile(const StudentsCollection& collection, std::ofstream& file, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		size_t len = strlen(collection.data[i].name);
		file.write((const char*)&len, sizeof(len));
		file.write(collection.data[i].name, len + 1);
		file.write((const char*)&collection.data[i].age, sizeof(collection.data[i].age));
		file.write(collection.data[i].fn, sizeof(collection.data[i].fn));
	}
}

int main()
{
	std::ofstream file("myFile.dat", std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "File can't be opened!" << std::endl;
		return -1;
	}

	std::cout << "Enter number of students: ";
	size_t n;
	std::cin >> n;

	StudentsCollection collection;
	collection.data = new Student[n];

	std::cout << "Write the students by name, age and fn:" << std::endl;
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

	writeStudentsToFile(collection, file, n);

	for (size_t i = 0; i < n; i++)
		delete collection.data[i].name;
	delete collection.data;

	file.close();
}