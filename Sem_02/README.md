# [Енумерации (Enums)](https://en.cppreference.com/w/cpp/language/enum)

## Enum (plain enum)
**Примери:**
```c++
enum Color { Red, Green, Blue, Purple, Orange };
enum Animal { Dog, Deer, Cat, Bird };
```

### Проблеми при използването на plain enums:
1. Не можем да имаме два изброителни типа, които съдържат повтарящи се енумератори (допустими стойности):
```c++
enum Gender { Male, Female };
enum Gender2 { Male, Female };
```

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_02/images/unscopedEnums.png)

2. Не можем да създадем променлива с име, което вече съществува като енумератор в някой enum:
```c++
enum Gender { Male, Female };

int main()
{
	int Male = 5;
}
```

3. При plain enums имаме **имплицитно конвертиране към int**, което води до проблеми:
```c++
enum Color { Red, Green, Blue, Purple, Orange };
enum Animal { Dog, Deer, Cat, Bird };

int main()
{
    Color color = Color::Red; // Same as Color color = Red
    Animal animal = Animal::Bird;

    int num = color; // no problem

    if (color == Animal::Dog) // no problem (bad)
        std::cout << "Bad, states that red color is equal to dog" << std::endl;

    if (animal == Color::Purple) // no problem (bad)
        std::cout << "Bad, states that bird is equal to purple color" << std::endl;
}
```

## Enum class (scoped enumeration)
Енъм класовете са **strongly typed** и **strongly scoped**, което решава споменатите проблеми на plain enums.
```c++
enum class Color { Red, Green, Blue, Purple, Orange };
enum class Animal { Dog, Deer, Cat, Bird };

int main()
{
    Color color = Color::Red;
    Animal animal = Animal::Dog;

    // int num = color; // error
    int num2 = static_cast<int>(color); // no problem

    // if (color == animal) // error (good)
    //    std::cout << "Bad, states that red color is equal to dog" << std::endl;
}
```

---

# [Namespaces](https://en.cppreference.com/w/cpp/language/namespace)
Пространствата от имена предоставят метод за предотвратяване на конфликти с имена.  
Символите, декларирани вътре в namespace block, се поставят в именуван scope, който не позволява да бъдат сбъркани със символи с идентични имена в други scope-ове.

```c++
namespace A
{
    int i = 5;
}
 
namespace B
{
    int i = 10;
    int j = 15;

    namespace C
    {
        namespace D
        {
            using namespace A; // names from A are injected into D

            int j = 20;
            int k = 25;
            int a = i; // i is B::i, because A::i is hidden by B::i
        }

        using namespace D; // names from D are injected into C

        int k = 30;   // OK to declare name identical to one introduced by a using
        // int l = k; // ambiguous: C::k or D::k
        int m = i;    // ok: B::i hides A::i
        int n = j;    // ok: D::j hides B::j
    }
}

namespace Q
{
    namespace V // V is a member of Q, and is fully defined within Q
    { 		// namespace Q::V // C++17 alternative to the lines above
        class C // C is a member of V and is fully defined within V
	{
		void m(); // C::m() is only declared
	};
        void f(); // f() is a member of V, but is only declared here
    }
 
    void V::C::m() // definition of V::C::m outside of the namespace (and the class body)
    {}
}

int main()
{
    std::cout << B::C::D::i << std::endl;
    std::cout << B::C::D::j << std::endl;
    std::cout << B::C::D::k << std::endl;
    std::cout << B::C::D::a << std::endl<<std::endl;
    
    std::cout << B::C::i << std::endl;
    std::cout << B::C::j << std::endl;
    std::cout << B::C::k << std::endl;
    std::cout << B::C::a << std::endl;
    std::cout << B::C::m << std::endl;
    std::cout << B::C::n << std::endl;
}
```

---

# Потоци (streams) и файлове.

Потокът е последователност от байтове.  

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_02/images/streams.gif)

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_02/images/streams.png)

**Видове потоци:**  
- Потоци за **вход (istream)**.  
- Потоци за **изход (ostream)**.  

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_02/images/ios.gif)

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

---

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

## [Режими на работа](https://en.cppreference.com/w/cpp/io/ios_base/openmode)
|ios|Резултат||  
|-|-|-|  
|ios::in|За извличане. Подразбира се за ifstream.|1|  
|ios::out|За вмъкване. Подразбира се за ofstream.|2|  
|ios::ate|За вмъкване. Не се гарантира, че старото съдържание на файла се запазва. При първото отваряне на файла, писането се осъществява в края на файла, след което позицията може да бъде променена.|4|  
|ios::app|За вмъкване. Старото съдържание на файла се запазва. Пише се само и единствено в края на файла.|8|  
|ios::trunc|Ако файлът съществува, съдържанието му се изтрива. Това поведение се подразбира за режима ios::out.|16|  
|ios::binary|Файлът се отваря в двоичен режим, не в текстов.|32|  

## [Флагове на състоянията на потока](https://en.cppreference.com/w/cpp/io/ios_base/iostate)
|   Флаг  | Значение |
|---------|----------|
| good()  | Потокът е в добро състояние, ако последната операция е била успешна. Това е най-общият флаг. За да е вдигнат, никой от останалите флагове не трябва да бъде вдигнат. |  
| bad()   | Потокът е в състояние bad, ако последната операция не е успешна. Възникнала е критична грешка по време на работата с потока, от която потокът не може да се възстанови. Например при хардуерен проблем. |  
| fail()  | Потокът е в състояние fail, ако последната операция не е успешна. Когато потокът е в състояние fail, той не е в състояние good. Пример за това е грешен формат на данните. Например очакваме да се прочете число, но от текущата позиция не може да се разпознае такова. С определени действия, състоянието на потока може да бъде възстановено и работата с него да продължи. |  
| eof()   | Флагът за край на файл eof (end of file) се вдига, ако е направен опит за четене след последния символ, а не при прочитането на последния символ. Заедно с него се вдига и флага fail, защото се търсят някакви данни, но такива не се откриват и операцията пропада. |  
| clear() | Ако състоянието на потока не е добро, то остава такова, докато не бъде възстановено. За да се възстанови обратно в състояние good, може да се използва функцията clear(). |  

## [seekg(), tellg(), seekp(), tellp()](https://en.cppreference.com/w/cpp/io/basic_istream/seekg)
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

**std::ios::beg** - Премества указателя от началото на файла до посочените байтове.  
**std::ios::end** - Премества указателя от края на файла до посочените байтове.  
**std::ios::cur** - Премества указателя от текущата му позиция във файла до посочените байтове.  

---

## Задачи

**Задача 1:** Да се напише програма, която *отпечатва собствения си код*.  

**Задача 2**: Да се напише функция, която *копира съдържанието на файл в друг файл*.  

**Задача 3:** Да се напише функция, която *намира големината на файл* (в байтове).  

**Задача 4**: Да се напише функция, която *връща броя редове във файл*.  

**Задача 5:** Да се напише функция, която *заменя всяко срещане на символ във файл с друг символ*. Съдържанието на файла **НЕ трябва да се зарежда в паметта**.  

**Задача 6:** Да се напише програма, която чете Comma-separated values (**CSV**) файл със студенти. За всеки студент има следната информация:  
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
