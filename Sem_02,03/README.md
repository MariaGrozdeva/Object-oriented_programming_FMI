# Потоци (streams) и файлове.

Потокът е последователност от байтове.  

![alt_text](https://i.ibb.co/r4P96vz/streams.png)

**Видове потоци:**  
- Потоци за **вход (istream)**.  
- Потоци за **изход (ostream)**.  

![alt_text](https://i.ibb.co/KVLkS4Q/fstream.gif)

***istream:*** Клас, в който е дефиниран оператор >>, както и член-функциите get(), getline(), read().  
***ostream:*** Клас, в който е дефиниран оператор <<, както и член-функциите put(), write().  
***iostream:*** Наследник на класовете istream и ostream. Притежава всички техни член-функции.  

cin - обект от класа istream  
cout - обект от класа ostream  

Примери за работа с **поток за вход**  
- Прочитане на символ
```c++
#include <iostream>

int main()
{
	char ch1, ch2;
	std::cin.get(ch1);
	std::cin >> ch2;
}
```
- Прочитане на изречение
```c++
#include <iostream>

int main()
{
	char sent[1024];
	std::cin.getline(sent, 1024);
}
```

Пример за работа с **поток за изход**
```c++
#include <iostream>

int main()
{
	std::cout.put('a');
	std::cout << "Output stream";
}
```

### Класове за работа с потоци за вход и изход от/към файл
**ifstream** (input file stream): Наследник на класа istream.  
**ofstream** (output file stream): Наследник на класа ostream.  

## Текстови файлове.

- Отваряне на файл за **четене**
```c++
#include <iostream>
#include <fstream>

int main()
{
    std::ifstream file("myFile.txt"); // Отваряме файла myFile.txt за четене

    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    file.close();
}
```

- **Четене** от файл
```c++
int main()
{
    std::ifstream file("myFile.txt");

    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    char a, b;
    file >> a >> b;

    std::cout << a << b; // a == първия символ от myFile.txt, b == втория символ от myFile.txt

    file.close();
}
```

- Прочитане на цялото съдържание на файл
```c++
#include <iostream>
#include <fstream>

const unsigned BUFF_SIZE = 1024;

int main()
{
    std::ifstream file("myFile.txt");

    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    char buff[BUFF_SIZE];
    while (!file.eof())
    {
        file.getline(buff, BUFF_SIZE);
        std::cout << buff << std::endl;
    }

    file.close();
}
```

- Отваряне на файл за **писане**
```c++
#include <iostream>
#include <fstream>

int main()
{
    std::ofstream file("myFile.txt"); // Отваряме файла myFile.txt за писане

    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    file.close();
}
```

- **Писане** във файл
```c++
int main()
{
    std::ofstream file("myFile.txt");

    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return -1;
    }

    char a = 'x', b = 'y';
    file << a << b; // съдържанието на myFile.txt == xy

    file.close();
}
```

## Режими на работа
|ios|Резултат||  
|-|-|-|  
|ios::in|Отваря файл за извличане.|1|  
|ios::out|Отваря файл за вмъкване. Ако файлът съществува, съдържанието му се изтрива.|2|  
|ios::ate|Указателят get се поставя в края на файла.|4|  
|ios::app|Указателят put се поставя в края на файла.|8|  
|ios::trunc|Ако файлът съществува, съдържанието му се изтрива.|16|  
|ios::binary|Превключва режима от текстов в двоичен.|32|  

## Флагове на състоянията на потока
|Флаг|Значение|  
|-|-|  
|bad()|Има загуба на информация. Някоя операция за четене/писане не е изпълнена.|  
|fail()|Последната входно/изходна операция е невалидна.|  
|eof()|Достигнат е краят на файла.|  
|good()|Всички операции са изпълнени успешно.|  
|clear()|Изчиства състоянието на потока (Вече good() ще върне истина).|  

## seekg(), tellg(), seekp(), tellp()
***seekg***  - премества get указателя на посочена позиция.  
Използва се, когато файл е отворен за извличане.  
```c++
file.seekg(10, std::ios::beg);
```
***tellg***  - връща позицията на get указателя.  
Използва се, когато файл е отворен за извличане.  
```c++
int pos = file.tellg();
```
***seekp***  - премества put указателя на посочена позиция.  
Използва се, когато файл е отворен за вмъкване.  
```c++
file.seekp(10, std::ios::beg);
```
***tellp***  - връща позицията на put указателя.  
Използва се, когато файл е отворен за вмъкване.  
```c++
int pos = file.tellp();
```
**ios::beg** - Премества указателя от началото на файла до посочените байтове.  
**ios::end** - Премества указателя от края на файла до посочените байтове.  
**ios::cur** - Премества указателя от текущата му позиция във файла до посочените байтове.  

## Задачи

**Задача 1:**  Да се напише програма, която *отпечатва собствения си код*.  

**Задача 2:** Да се напише програма, която чете Comma-separated values (**CSV**) файл със студенти. За всеки студент има следната информация:  
**първо име**, **фамилно име**, **имейл**, **факултетен номер**.
Със стартирането на програмата потребителят въвежда име на файл, който да бъде зареден в паметта.  

1.  Да се напише функция, която след зареждане на файла *отпечатва на стандартния изход информация за студента при подаден факултетен номер*.
2.  Да се напише функция, която *по подаден факултетен номер и низ променя email-a на студента, който има дадения факултетен номер, с подадения низ*.
3.  Да се напише функция, която *приема низ (име на файл) и запазва студентите в същия формат (**CSV**)*. Т.е. при повторно пускане, програмата да може да прочете новия генериран файл.

Да се реализира прост интерфейс, с който да се извикват написаните функции през конзолата.  

**Пример**  (входът от потребителя започва с '>'):
```c++
Open file:
>students.csv
File successfully opened!
>print 21245
Name: Robert Angelov, Email: robert@yahoo.com, FN: 21245
>edit 21245 robert@abv.bg
>print 21245
Name: Robert Angelov, Email: robert@abv.bg, FN: 21245
>save students2.csv
File students2.csv successfully saved!
```

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
    file.write((const char*)&num, sizeof(num));

    file.close();
}
```
Как изглежда файлът?  

![alt_text](https://i.ibb.co/2nkCysZ/binFile.png)

Как да го прочетем?  

![alt_text](https://i.ibb.co/nnSQz2v/bin-File-Content.png)
Съдържанието на файла (числото 1000) в шестнайсетична бройна система.  
Байтовете се записват в **обратен ред**. Най- старшият байт е последен. Шестнайсетичното представяне на 1000_(10) е **00 00 03 E8_(16)**, което записано наобратно е точно **E8 03 00 00**.  

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
    file.read((char*)&toRead, sizeof(num));

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
    file.write((const char*)&test, sizeof(test));

    file.close();
}
```

Как изглежда файлът?  

![alt_text](https://i.ibb.co/jvQGrbL/binFile2.png)

"Разчетен:"  

![alt_text](https://i.ibb.co/m8hRsfY/bin-File2-Content2.png)

- **Записване** на структура, **която използва динамична памет**, в двоичен файл  

**Задача:** Да се напише програма, която:  
- записва колекция от студенти в двоичен файл,
- чете колекция от студенти от двоичен файл.  

Всеки студент има **име - низ с произволна дължина**, **години** и **факултетен номер**.  
