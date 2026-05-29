# Множествено наследяване
Множественото наследяване позволява един клас да наследи множество класове.

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_13/images/Multiple_Inheritance.png)

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

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_13/images/ConstrDestr-Multiple_Inheritance.png)

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

## Диамантен проблем
![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_13/images/Diamond.jpg)

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

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_13/images/Multiple_Inheritance1.png)

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

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_13/images/Multiple_Inheritance2.png)

❗ Конструкторите с параметри на виртуални класове трябва да се извикват от конструкторите на всички класове, които са техни наследници, а не само от конструкторите на преките им наследници.

```c++
D::D(...) : B(...), C(...), A(...) {} // We call the constructor of A explicitly.
```
