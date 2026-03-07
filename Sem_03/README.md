## Двоични файлове.
"Разбираеми" за компютъра, "неразбираеми" за нас.  

- Отваряне на двоичен файл за **четене**  
```c++
#include <iostream>
#include <fstream>

int main()
{
    // ..
    std::ifstream file("myFile.dat", std::ios::binary);
    // ..
}
```

- Отваряне на двоичен файл за **писане**  
```c++
#include <iostream>
#include <fstream>

int main()
{
    // ..
    std::ofstream file("myFile.dat", std::ios::binary);
    // ..
}
```

- **Записване** на число в двоичен файл  
```c++
#include <iostream>
#include <fstream>

int main()
{
    std::ofstream file("myFile.dat", std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    int num = 1000;
    file.write(reinterpret_cast<const char*>(&num), sizeof(num));

    file.close();
}
```
Как изглежда файлът?  

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_03/images/binFile1.png)  

Как да го прочетем?  

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_03/images/binFile1HexViewer.png)  
Съдържанието на файла (числото 1000) в шестнайсетична бройна система.  

Байтовете са записани в **обратен ред** (най- старшият байт е последен), защото програмата е изпълнена на машина с **little endian** процесорна архитектура.  
Шестнайсетичното представяне на 1000_(10) е **00 00 03 E8_(16)**, което записано наобратно е точно **E8 03 00 00**.  

- **Прочитане** на число от двоичен файл  
```c++
#include <iostream>
#include <fstream>

int main()
{
    std::ifstream file("myFile.dat", std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    int toRead;
    file.read(reinterpret_cast<char*>(&toRead), sizeof(num));

    file.close();
}
```
