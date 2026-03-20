#include "Event.h"

int main()
{
	Event e("Party", 31, 5, 2024, 20, 30, 00, 23, 30, 00);
	std::cout << e.getName();
}