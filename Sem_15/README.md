# Множествено наследяване
Множественото наследяване позволява един клас да наследи множество класове.

![alt_text](https://i.ibb.co/zGscdZ9/Multiple-Inheritance.png)

### Конструктори и деструктори при множествено наследяване:
```c++
struct MyClass : SuperClass1, SuperClass2, SuperClass3, SuperClass4
{
	MyClass()
	{
		std::cout << "MyClass()" << std::endl;
	}
	~MyClass()
	{
		std::cout << "~MyClass()" << std::endl;
	}
};

int main()
{
	MyClass obj;
}
```

![alt_text](https://i.ibb.co/82xJ2JK/Constr-destr-Mult-Inh.png)

### Копиране при множествено наследяване:
```c++
MyClass(const MyClass& other) : SuperClass1(other), SuperClass2(other), SuperClass3(other), SuperClass4(other)
{
	copyFrom(other);
}

MyClass(const MyClass& other)
{
	if (this != &other)
	{
		SuperClass1::operator=(other);
		SuperClass2::operator=(other);
		SuperClass3::operator=(other);
		SuperClass4::operator=(other);

		free();
		copyFrom(other);
	}
}
```

---

## Диамантен проблем
![alt_text](https://i.ibb.co/VW52qKC/Diamond.jpg)

**Проблем**: Многократно наследяване на базов клас – нееднозначност при използване на данните му. В класа **D** има два обекта от тип **A**.

Ако действително желаното поведението е да имаме два различни обекта от тип А в класа D, то при използване на данните на А задължително трябва да посочим тези от кой родител използваме:

```c++
struct A { int a = 4; };
struct B : A {};
struct C : A {};

struct D : B, C 
{
	void f()
	{
		B::a++; // OK! No ambiguity!
	}
};
```

В повечето случаи, обаче, това, което искаме като поведение е характеристиките на А да бъдат наследени само веднъж. Това става чрез използване на т.н. **виртуални базови класове**. Когато базов клас е обявен за виртуален, всички класове, които го наследяват, **споделят единствено негово копие**.

Обявяваме класа A за виртуален базов клас по следния начин:
```c++
// Syntax 1
class B : virtual public A 
{
};

// Syntax 2
class C : public virtual A
{
};
``` 

![alt_text](https://github.com/MariaGrozdeva/OOP_private/blob/main/Sem_14/img/Multiple_Inheritance1.png)

```c++
struct A { int a = 4; };
struct B : virtual A {};
struct C : virtual A {};

struct D : B, C 
{
	void f()
	{
		a++; // OK! No ambiguity!
	}
};
```

![alt_text](https://github.com/MariaGrozdeva/OOP_private/blob/main/Sem_14/img/Multiple_Inheritance2.png)

❗ Конструкторите с параметри на виртуални класове трябва да се извикват от конструкторите на всички класове, които са техни наследници, а не само от конструкторите на преките им наследници.

```c++
D::D(...) : B(...), C(...), A(...) {} // We call the constructor of A explicitly.
```

[Bjarne Stroustrup – Multiple Inheritance for C++](https://www.usenix.org/legacy/publications/compsystems/1989/fall_stroustrup.pdf)

---

# Шаблони (templates)

**Какво е шаблон?**  
Функция или клас, която/който работи не с променливи от конкретно дефиниран тип, а с абстрактни променливи, се нарича шаблонна функция/клас.  

**Пример:**
```c++
template <typename T>
const T& myMax(const T& lhs, const T& rhs)
{
	return lhs < rhs ? rhs : lhs;
}

int main()
{
	std::cout << myMax(24, 22);
}
```

Компилаторът генерира т. нар. шаблонна функция, като замества параметрите на шаблона с типовете на съответните фактически параметри.  

:bangbang: Не можем да разделяме шаблонни класове в .h и .cpp файлове. **Трябва да пишем декларацията и дефиницията им в един файл** – например .hpp файл. Причината е следната:  

Да си представим, че имаме следната структура:
```c++
template <typename T>
struct Foo
{
    T bar;
    void doSomething(const T& param);
};
```
Създаваме инстанция от тази структура:
```c++
int main()
{
	Foo<int> f;
}
```
След като "прочете" този ред, компилаторът ще създаде следния клас:
```c++
struct Foo
{
    int bar;
    void doSomething(const int& param);
};
```
Съответният .cpp файл "не разбира" за създаването на този хедър и кодът не се компилира.  

Ако предварително знаем с какви конкретни типове ще бъде инстанциран шаблонният клас, то можем да заобиколим този проблем като накрая на .cpp файла добавим:
```c++
template struct Foo<int>;
template struct Foo<double>;
// ...
```

---

## Специализация на шаблони
```c++
template <typename T>
void sort(T* arr, size_t size)
{
    // code to implement Quick Sort
}
 
 // specialized for char data type
template <>
void sort<char>(char* arr, size_t size)
{
    // code to implement Count Sort
}
```