# Конструктори и деструктор.

Бихме искали **инициализирането** на обект и **освобождаването на динамично заделена** памет да се извършват "автоматично", а не ние да извикваме поотделно двете функции (с цел да се избегнат грешки).  

Всяка структура/клас може да има n на брой конструктори и **само един** деструктор.  
Това са специални функции, които компилаторът ще извика автоматично вместо нас.  

**Жизнен цикъл на обект**:  
- Създаване на обект в даден scope - заделя се памет и член-данните се инициализират.
- Достига се до края на блока.
- Обектът и паметта, която е асоциирана с него, се разрушават.

**Конструктор**:  
- Извиква се веднъж - **при създаването на обекта**.
- **Не се оказва експлицитно тип на връщане** (връща константна референция).
- Има **същото име като класа**.

**Деструктор**:  
- Извиква се веднъж - **при изтриването на обекта**.
- **Не се оказва експлицитно тип на връщане**.
- Има **същото име като класа със симовла '~'** в началото.

```c++
struct DynamicArray
{
	int* data;
	size_t used;
	size_t allocated;

	DynamicArray() // Default constructor
	{
		data = nullptr;
		used = 0;
		allocated = 0;
	}
	~DynamicArray()
	{
		delete[] data;
	}

	void allocate(size_t size)
	{
		data = new int[size];
		used = 0;
		allocated = size;
	}
	int& at(size_t index)
	{
		return data[index];
	}
};

int main()
{
	DynamicArray da; // DynamicArray::DynamicArray()
	da.allocate(100);
	da.at(5) = 22;

	// DynamicArray::~DynamicArray()
}
```
```c++
struct DynamicArray
{
	int* data;
	size_t used;
	size_t allocated;

	DynamicArray()
	{
		data = nullptr;
		used = 0;
		allocated = 0;
	}
	DynamicArray(size_t size) // Parameterized constructor
	{
		data = new int[size];
		used = 0;
		allocated = size;
	}
	~DynamicArray()
	{
		delete[] data;
	}

	int& at(size_t index)
	{
		return data[index];
	}
};
```

# Ред на работа на конструктурите и деструктурите.

```c++
class A
{
	int a;
public:
	A()
	{
		std::cout << "A()" << std::endl;
	}
	~A()
	{
		std::cout << "~A()" << std::endl;
	}
};

class B
{
	int b;
public:
	B()
	{
		std::cout << "B()" << std::endl;
	}
	~B()
	{
		std::cout << "~B()" << std::endl;
	}
};

class C
{
	A a;
	B b;
	int c;
public:
	C()
	{
		std::cout << "C()" << std::endl;
	}
	~C()
	{
		std::cout << "~C()" << std::endl;
	}
};

int main()
{
	C obj;
}
```
Изход:  

![alt_text](https://i.ibb.co/ZVL7m0d/Constr-Destr.png)

:bangbang: Когато имаме клас X, в който имаме обекти от други класове (A, B) и последните нямат конструктори по подразбиране, задължително **в конструктора на X трябва експлицитно да извикаме конструкторите на A и B**.

```c++
class A
{
	int a;
public:
	A(int value) : a(value * 2) 
	{}
};

class B
{
	int b;
public:
	B(int value) : b(value / 2)
	{}
};

class X
{
	A a;
	B b;
	int c;
public:
	X(int value) : a(value), b(value), c(value * 5) // Call A(value) and B(value)
	{}
};

int main()
{
	X obj(23);
}
```

## Задача
Да се реализира **class Time** за работа с часове.  
Класът трябва да съдържа поне следните методи:

- **Подразбиращ се контруктор**, който създава часа *00:00:00*.
- **Конструктор, който приема три параметъра** - час, минути и секунди.

- **int compare()** - *сравнява часa с друг, който е подаден като параметър*. Ако последният е в по-ранен момент, да се върне положително число, ако е в по- късен - отрицателно. Ако двата часа съвпадат, да се върне 0.

- **getToMidnight()** - връща *колко време остава до полунощ*.

- **bool isDinnerTime()** - *връща истина, ако е време за вечеря* (между 20:30 и 22:00 часа).

- **bool isPartyTime()** - *връща истина, ако е време за купон* (между 23:00 и 6:00 часа).

- **print(bool is12hoursClock)** - *отпечатва часа на екрана*. Ако променливата е истина, часът се отпечатва във формат  ***10:45:32PM***, ако е лъжа - ***22:45:32***.
