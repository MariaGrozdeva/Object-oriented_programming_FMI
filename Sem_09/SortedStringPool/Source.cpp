#include "SortedStringPool.h"

int main()
{
	SortedStringPool pool;

	pool.add("aaa");
	pool.add("bbb");
	pool.add("ccc");
	std::cout << pool << std::endl << std::endl;

	pool.add("ab");
	pool.add("bc");
	std::cout << pool << std::endl << std::endl;

	pool.add("aaa");
	std::cout << "After adding one more \"aaa\": " << pool << std::endl << std::endl;

	std::cout << "Index of \"aaa\": " << pool.contains("aaa") << std::endl << std::endl;

	pool.removeAt(0);
	std::cout << "After removing \"aaa\": " << pool << std::endl << std::endl;

	std::cout << "Index of \"aaa\": " << pool.contains("aaa") << std::endl << std::endl;

	pool.removeAt(0);
	std::cout << "After removing \"aaa\": " << pool << std::endl << std::endl;

	std::cout << "Index of \"aaa\": " << pool.contains("aaa") << std::endl << std::endl;
}