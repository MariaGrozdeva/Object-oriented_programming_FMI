#include <fstream>

int main()
{
	std::ofstream ofs("file.dat", std::ios::binary);
	if (!ofs.is_open())
	{
		return -1;
	}

	int arr[] = { 1, 2, 3, 4, 5 };
	ofs.write(reinterpret_cast<const char*>(arr), sizeof(arr));

	ofs.close();
}
