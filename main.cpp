
#include "ComputerPartWriter.h"
#include "ComputerPartReader.h"


int main() {
	
	ComputerPart CParr1[5];

	CParr1[0].setComputerPartOnce("Sony", "Xperia", 150, 1, "MONITOR");
	CParr1[1].setComputerPartOnce("Samsung", "S21", 250, 2, "CAMERA");
	CParr1[2].setComputerPartOnce("Philips", "One Blade", 350, 3, "COMPUTER");
	CParr1[3].setComputerPartOnce("HP", "Legion", 450, 4, "LAPTOP");
	CParr1[4].setComputerPartOnce("Acer", "Nitro", 550, 5, "MOUSE");

	std::cout << "Array 1:";
	for (int i = 0; i < 5; ++i)
		CParr1[i].print();


	ComputerPartWriter writer("NotMyFile.txt");
	for (size_t i = 0; i < 5; i++)
	{
		writer.writeCPInFile(CParr1[i]);
	}


	ComputerPart CParr2[5];
	ComputerPartReader reader("NotMyFile.txt");
	std::cout << "\n\nArray 2:";
	for (size_t i = 0; i < 5; i++)
	{
		reader.readCPFromFile(CParr2[i]);
		CParr2[i].print();
	}



	std::cout << "\n\n";
}
