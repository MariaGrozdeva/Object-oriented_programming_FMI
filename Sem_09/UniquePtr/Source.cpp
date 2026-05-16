#include <iostream>
#include "UniquePtr.hpp"

struct A
{
	A(int a, int b) : a(a), b(b)
	{}
	int a;
	int b;
};

int main()
{
	UniquePtr<A> p1 = myMakeUnique<A>(5, 23);
	std::cout << p1->a << " " << p1->b << "\n";

	UniquePtr<A> p2 = std::move(p1);
	std::cout << "p1 null: " << !p1 << "\n";
	std::cout << (*p2).a << "\n";

	p2.reset();
	std::cout << "p2 null: " << !p2 << "\n";

	return 0;
}
