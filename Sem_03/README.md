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

- **Записване** на структура, **която НЕ използва динамична памет**, в двоичен файл  

В текстовите файлове структура се записва като последователно запишем елементите й. В двоичните файлове можем да я запишем "наведнъж".  
```c++
#include <iostream>
#include <fstream>

const unsigned MAX_SIZE = 1024;
struct Test
{
    bool b;
    int i;
    char str[MAX_SIZE];
};

int main()
{
    std::ofstream file("myFile.dat", std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    Test test{ true, 2022, "Test" };
    file.write(reinterpret_cast<const char*>(&test), sizeof(test));

    file.close();
}
```

Как изглежда файлът?  

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_03/images/binFile2.png)  

"Разчетен:"  

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_03/images/binFile2HexViewer.png)  

---

## Задачи

**Задача 1:** Да се напише програма, която:  
- записва масив от цели числа в двоичен файл,
- чете масив от цели числа от двоичен файл.  

**Задача 2:** Да се напише програма, която:  
- записва колекция от студенти в двоичен файл,
- чете колекция от студенти от двоичен файл.  

Всеки студент има **име - низ с произволна дължина**, **години** и **факултетен номер**.  

**Задача 3:** Да се напише програма за изглед и модификация на двоични файлове **(hex viewer)**. При стартиране на програмата трябва да се въведе път до двоичен файл и да се зареди съдържанието му в паметта. Програмата трябва да поддържа следните функционалности:

1. Преглед на файла (**view**) — отпечатва байтовете, записани във файла, в шестнайсетична бройна система. След това байтовете се отпечатват, интерпретирани като ASCII символи. Ако байтът съответства на малка/главна латинска буква, то тя се отпечатва. В противен случай се отпечатва точка.
2. Добавяне на байт в края (**add**).
3. Промяна на байт по индекс (**change**).
4. Запазване на промените в същия файл (**save**).
5. Запазване на промените в друг файл (**save as**).

Да се реализира прост интерфейс, с който да се извикват написаните функции през конзолата.  

**Пример**  (входът от потребителя започва с '>'):

Нека имаме двоичен файл myData.dat, който се е получил след изпълнението на следния код:

```c++
int x = 25409;
ofstream file(“myData.dat”, ios::binary);
file.write(reinterpret_cast<const char*>(&x), sizeof(x));
```

```c++
Enter a file path:
> myData.dat
File loaded successfully. Size: 4 bytes
> view
41 63 00 00
A  c  .  .
> change 1 65
Operation executed successfully.
> view
41 65 00 00
A  e  .  .
> save
File successfully saved.
```
