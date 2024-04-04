#include "Set.h"

int main()
{
        std::cout << "s1: ";
	Set s1(1024);
	s1.add(1);
	s1.add(10);
	s1.add(5);
	s1.add(22);
	s1.add(23);
	s1.add(24);
	s1.print();

        std::cout << "s2: ";
	Set s2(50);
	s2.add(1);
	s2.add(17);
	s2.add(49);
	s2.remove(49);
	s2.print();
	
	Set unionRes = unionOfSets(s1, s2);
	Set intersectionRes = intersectionOfSets(s1, s2);

        std::cout << "union of s1 and s2: ";
	unionRes.print();
	std::cout << "intersection of s1 and s2: ";
	intersectionRes.print();
}
