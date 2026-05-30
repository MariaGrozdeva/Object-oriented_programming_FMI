#include "SetCalculator.h"
#include <iostream>

int main()
{
	SetCalculator s("(((A^B)vC)vX)");

	SetCalculator::Element el;
	el.set('A', true);
	el.set('B', true);
	el.set('C', true);

	std::cout << s.isElementIn(el) << std::endl;

	// (AvB) and (BvA) are the same set - union is commutative
	SetCalculator s1("(AvB)");
	SetCalculator s2("(BvA)");
	std::cout << s1.isSameSet(s2) << std::endl; // 1

	// (A^B) and (AvB) are NOT the same set
	SetCalculator s3("(A^B)");
	SetCalculator s4("(AvB)");
	std::cout << s3.isSameSet(s4) << std::endl; // 0

	// A\B and A^(!B) are the same set - set difference equals intersection with complement
	SetCalculator s5("(A\\B)");
	SetCalculator s6("(A^(!B))");
	std::cout << s5.isSameSet(s6) << std::endl; // 1
}
