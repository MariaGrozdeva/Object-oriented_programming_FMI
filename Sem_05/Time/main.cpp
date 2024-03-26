#include "Time.h"

int main()
{
	Time t(15, 15, 33);
	t.serialize(std::cout);

	t.tick();
	t.tick();
	t.serialize(std::cout);
}