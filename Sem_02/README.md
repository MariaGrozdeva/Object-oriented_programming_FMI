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
