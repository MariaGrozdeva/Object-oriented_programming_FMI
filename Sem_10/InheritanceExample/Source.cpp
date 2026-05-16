#include "Student/Student.h"
#include "Teacher/Teacher.h"

int main()
{
    Student s1("Alice", 20, 12345);
    s1.print();
    std::cout << std::endl;

    Student s2 = s1;
    s2.setFn(99999);
    s2.print();
    std::cout << std::endl;

    const char* subjects[] = { "Math", "Physics", "Algorithms" };
    Teacher t1("Bob", 45, subjects, 3);
    t1.print();
    std::cout << std::endl;

    t1.addSubject("OOP");
    t1.print();
    std::cout << std::endl;

    Teacher t2 = std::move(t1);
    t2.print();

    return 0;
}
