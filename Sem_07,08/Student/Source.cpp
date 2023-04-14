#include "Student.h"
#include <iostream>

int main()
{
	Student student;
	unsigned int grades[] = { 2,4,6 };

	student.setName("Ivan");
	student.setGrades(grades, sizeof(grades) / sizeof(unsigned int));
}