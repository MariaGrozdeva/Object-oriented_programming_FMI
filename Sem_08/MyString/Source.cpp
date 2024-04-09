#include "MyString.h"

int main()
{
    try
    {
	    MyString str1("OOP");
	    MyString str2(" is great!");
	    str1 += str2;
	    
	    std::cout << str1 << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
