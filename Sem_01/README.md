## Структури

"**C++ struct**, short for C++ Structure, is an **user-defined data type** available in C++".  
Фундаментални типове данни - int, double, bool, char,..  
Структурите в C++ са **съставен тип данни**. Използват се за групиране на елементи. Елементите могат да бъдат **от различен тип** и **с различна дължина**.  
Последното е точно това, което различава структурите от масивите. В масивите съхраняваме данни от **еднакъв тип**.

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

### Масиви от инстанции
```c++
Person arr1[22];

Person* arr2 = new Person[23];
delete[] arr2;
```

### Структури в паметта
Елементите на всяка структура "вървят в комплект". Те се записват последователно в паметта точно в реда, в който сме ги изредили в структурата.  
#### Подравняване (alignment)
:heavy_exclamation_mark: Поради начина на работа на процесора, имаме следното правило:  
Ако S е размерът на променливата V, тази променлива трябва да бъде записана на адрес, кратен на S, т.е.  address(V) % S == 0.  
Когато работим с фундаментални типове, компилаторът се грижи за коректното им подравняване.  
Когато работим със структури, ние трябва да осигурим оптималното "подреждане" на елементите им, имайки предвид подравняванията.  
```c++
struct Test
{
	int i1; // sizeof(int) == 4
	char c; // sizeof(char) == 1
	int i2; // sizeof(int) == 4
};
```
На пръв поглед, за създаване на инстанция на структурата Test са ни нужни 9 байта памет. Но само на пръв поглед.  

![alt_text](https://i.ibb.co/LQL4tMR/Padding.png)

Т.е. за създаване на такава инстанция са ни нужни 4 (sizeof(i1)) + 1 (sizeof\(c\)) + 3 (padding) + 4 (sizeof(i2)) = 12 байта.  

```c++
struct Test
{
	char c1; // sizeof(char) == 1
	int i1; // sizeof(int) == 4
	char c2; // sizeof(char) == 1
	int i2; // sizeof(int) == 4
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
	char c1; // sizeof(char) == 1
	char c2; // sizeof(char) == 1
	int i1; // sizeof(int) == 4
	int i2; // sizeof(int) == 4
};

int main()
{
	Test t;
	std::cout << sizeof(t); // 12
}
```
Извод: Само чрез пренареждане на елементите на структурата можем да "пестим" памет (В горния пример "спестихме" 4 байта (25%) памет.  

## Задача:
Въвежда се цяло число **N**, последвано от **N** тригъгълника в равнината, всеки от които се определя от 3 точки (6 координати). Отпечатайте лицата им в сортиран вид.  
