#include "Person.h"

int main()
{
	Person p1("Robert", 35);
	Person p2(p1); // Copy constructor
	Person p3("George", 26);
	Person p4 = p3; // Copy constructor
	p4 = p1; // Operator=

	p1.print();
	p2.print();
	p3.print();
	p4.print();
}