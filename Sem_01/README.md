# Преговор

1. [Указатели и референции](https://github.com/MariaGrozdeva/Introduction_to_programming_FMI/tree/main/Sem_07)

2. Видове памет:
<img style="object-fit:contain;" align="right" width="450" height="600" src="https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_01/images/memory.png">

Паметта, която използваме в C++, се разделя на четири основни типа:
- **Глобална (статична)**: в тази памет се записват статични/глобални променливи.
- **Автоматична (stack)**: тя съдържа "локалните" променливи, т.е. онези, които са дефинирани в телата на функции и са същевременно нестатични.
	- Заделя се в момента на дефиниция на променливите и се освобождава в момента на изход от scope-a, в която е дефинирана;
	- Последно заделената памет се освобождава първа (First in Last out);
	- Количеството заделена памет е определено по време на компилация;
	- Ние нямаме контрол над управлението над тази памет.
 - **Динамична (heap)**: е "свободната" част от паметта, която се използва (<em>динамично</em>) в хода на програмата.
	- Заделя се и се освобождава по всяко време на изпълнение на програмата;
	- Областта за динамична памет е набор от свободни блокове памет;
	- Програмата може да заяви блок с произволна големина;
	- Имаме контрол над управлението й.
-	**Program Code**: памет, в която се пази нашият компилиран код
	- Може да се достъпва с function pointer-и.

---

# Обектно-ориентирано програмиране
![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_01/images/oop.png)

Обектно-ориентирано програмиране е **програмна парадигма**, при която една програмна система се моделира като набор от обекти, които взаимодействат помежду си, за разлика от традиционното виждане, при което една програма е списък от инструкции, които процесорът изпълнява. Всеки обект е способен да получава съобщения, обработва данни и праща съобщения на други обекти.

### Принципи:
- Абстракция
  - процесът на скриване на ненужни подробности от потребителя
- Капсулация
  - един обект трябва да предоставя на ползвателя само пряко необходимите му средства за управление
- Наследяване
  - позволява да бъдат дефинирани и създавани обекти, които са специализирани варианти на вече съществуващи обекти;
  - класът наследник взема всички свойства и методи на класа-родител
- Полиморфизъм
  - едни и същи действия се реализират по различен начин в зависимост от обектите, върху които се прилагат

---

# [**Структури**](https://en.cppreference.com/w/c/language/struct)

"**C++ struct**, short for C++ Structure, is an **user-defined data type** available in C++".  
Фундаментални типове данни - int, double, bool, char,..  
Структурите в C++ са **съставен тип данни**. Използват се за групиране на елементи. Елементите могат да бъдат **от различен тип** и **с различна дължина**.  
Последното е точно това, което различава структурите от масивите. В масивите съхраняваме само **хомогенни данни** (такива от **един и същ тип**).

```c++
struct Person
{
	char firstName[32];
	char lastName[32];
	unsigned int age;
	char ucn[11]; // unified civilian number
};
```

### Деклариране и дефиниране на инстанции в стека
```c++
Person p; // default values are assigned

Person p2 = { "Ivan", "Dimitrov", 25, "9612120305" }; // firstName == Ivan, lastName == Dimitrov, age == 25, ucn == 9612120305

Person p3;
strcpy(p3.firstName, "Ivan");
strcpy(p3.lastName, "Dimitrov");
p3.age = 25;
strcpy(p3.ucn, "9612120305");
```

### Деклариране и дефиниране на инстанции в динамичната памет
```c++
Person* p1 = new Person({ "Ivan", "Dimitrov", 25, "9612120305" });

Person* p2 = new Person();
strcpy((*p2).firstName, "Ivan");
strcpy((*p2).lastName, "Dimitrov");
(*p2).age = 25;
strcpy((*p2).ucn, "9612120305");
```
Използваме "obj->data" вместо (*obj).data.
```c++
Person* p2 = new Person();
strcpy(p2->firstName, "Ivan");
strcpy(p2->lastName, "Dimitrov");
p2->age = 25;
strcpy(p2->ucn, "9612120305");
```
:heavy_exclamation_mark: Изтриваме динамичната памет.
```c++
delete p1;
delete p2;
```

---

### Влагане на инстанции
```c++
struct Person
{
	char firstName[32];
	char lastName[32];
	unsigned int age;
	char ucn[11]; // unified civilian number
};
struct Family
{
	Person mother;
	Person father;
	unsigned int numberOfChildren;
};

int main()
{
	Family f = { {"Tanya", "Georgieva", 33, "8901015437"}, {"Anton", "Georgiev", 34, "8802024573"}, 2 };
}
```

---

### Масиви от инстанции
```c++
Person arr1[22];

Person* arr2 = new Person[23];
delete[] arr2;
```

---

### Подаване на инстанции във функции
:heavy_exclamation_mark: Ако няма да променяме инстанцията, я подаваме по **константна референция.**
```c++
void printByTwoNames(const Person& p)
{
	std::cout << p.firstName << ' ' << p.lastName;
}
```
Можем и да я променяме.
```c++
void readPerson(Person& p)
{
	std::cin >> p.firstName >> p.lastName >> p.age >> p.ucn;
}
```
Можем да я подаваме по копие.
```c++
Person changeLastName(Person p, const char* newName)
{
	strcpy(p.lastName, newName);
	return p;
}
```

### Връщане на инстанции от функции

```c++
const size_t MAX_SIZE = 32;

struct Person
{
	int age;
	char name[MAX_SIZE];
};

Person returnPersonValue(Person& p)
{
	return p;
}

Person& returnPersonByRef(Person& p)
{
	return p;
}

int main()
{
	{
		Person p = { 55, "Ivan" };
		Person p2 = returnPersonValue(p);
		p2.age = 100;
		std::cout << p.name << ' ' << p.age << ' ' << p2.age << std::endl; // 55 100
	}

	{
		Person p = { 55, "Anton" };
		Person p2 = returnPersonByRef(p);
		p2.age = 100;
		std::cout << p.name << ' ' << p.age << ' ' << p2.age << std::endl; // 55 100
	}

	{
		Person p = { 55, "Georgi" };
		Person& p2 = returnPersonByRef(p);
		p2.age = 100;
		std::cout << p.name << ' ' << p.age << ' ' << p2.age << std::endl; // 100 100
	}
}
```

---

## Структури в паметта
Елементите на всяка структура "вървят в комплект". Те се записват последователно в паметта точно в реда, в който сме ги изредили в структурата.  
#### Подравняване (alignment)
:heavy_exclamation_mark: Поради начина на работа на процесора, имаме следното правило:  
Ако S е размерът на променливата V, то тази променлива трябва да бъде записана на адрес, кратен на S, т.е.  address(V) % S == 0.  
Когато работим с фундаментални типове, компилаторът се грижи за коректното им подравняване.  
Когато работим със структури, ние трябва да осигурим оптималното "подреждане" на елементите им, имайки предвид подравняванията.  
```c++
struct Test
{
	std::int32_t i1;
	char c
	std::int32_t i2;
};
```
На пръв поглед, за създаване на инстанция на структурата Test са ни нужни 9 байта памет. Но само на пръв поглед.  

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_01/images/padding.png)

Т.е. за създаване на такава инстанция са ни нужни 4 (sizeof(i1)) + 1 (sizeof\(c\)) + 3 (padding) + 4 (sizeof(i2)) = 12 байта.  

```c++
struct Test
{
	char c1;
	std::int32_t i1;
	char c2;
	std::int32_t i2;
};

int main()
{
	Test t;
	std::cout << sizeof(t); // 16
}
```
```c++
struct Test
{
	char c1;
	char c2;
	std::int32_t i1;
	std::int32_t i2;
};

int main()
{
	Test t;
	std::cout << sizeof(t); // 12
}
```
Извод: Само чрез пренареждане на елементите на структурата можем да "пестим" памет (В горния пример "спестихме" 4 байта (25%) памет.  

---

# [**Обединения**](https://en.cppreference.com/w/cpp/language/union)
Обединенията използват едно и също място в паметта за всеки от своите членове, т.е адресът на всички член-данни е един и същ.  
Променливите, поделящи паметта, могат да са от различни типове.  
Във всеки един момент обаче може да се използва само една променлива от състава на обединението. Недефинирано поведение е да се чете променлива от обединението, която не е последната променена.
```c++
union S
{
    std::int32_t n;
    std::uint16_t s[2];
    std::uint8_t c;
};
 
int main()
{
    std::cout << sizeof(S) << std::endl; // 4
    S s = {0x12345678}; // initializes the first member, s.n is now the active member
    // at this point, reading from s.s or s.c is undefined behavior
    std::cout << std::hex << s.n << std::endl; // 12345678
    s.s[0] = 0x0011; // s.s is now the active member
    // at this point, reading from n or c is UB but most compilers define it
    std::cout << std::hex << +s.c << std::endl; // 11 or 00, depending on platform
    std::cout << std::hex << s.n << std::endl; // 12340011 or 00115678
}
```

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_01/images/union.jpg)

---

## Задача:
Въвежда се цяло число **N**, последвано от **N** тригъгълника в равнината, всеки от които се определя от 3 точки (6 координати). Отпечатайте лицата им в сортиран вид.  
