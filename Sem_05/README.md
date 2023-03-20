# Член-функции (методи). Конструктори и деструктор.

```c++
struct DynamicArray
{
	int* data;
	size_t used;
	size_t allocated;
};

void initialise(DynamicArray& da)
{
	da.data = nullptr;
	da.used = 0;
	da.allocated = 0;
}
void allocate(DynamicArray& da, size_t size)
{
	da.data = new int[size];
	da.used = 0;
	da.allocated = size;
}
void free(DynamicArray& da)
{
	delete[] da.data;
	da.data = nullptr;
	da.used = 0;
	da.allocated = 0;
}

void push_back(DynamicArray& da, int el)
{
	if (da.used >= da.allocated)
	{
	    // resize(allocated * 2);
	}
	da.data[da.used++] = el;
}
int get(const DynamicArray& da, unsigned int index)
{
	assert(index < da.used);
	return da.data[index];
}

int main()
{
	DynamicArray da;
	initialise(da);
}
```
Горният програмен фрагмент е напълно валиден.  
Но всички написани функции се отнасят за структурата DynamicArray. Не можем ли да ги "групираме" по някакъв начин?  

## Член-функции

- Функции, които **не съществуват глобално**.
- Имената им са от вида **\<ClassName\>::\<memberFunctionName\>**
- **Работят с член-данните на инстанцията/обекта** от дадена структура/клас.
- **Извикват се с инстанция/обект** на структурата/класа.
- Компилаторът преобразува всяка член-функция на дадена структура/клас в обикновена функция с уникално име и един допълнителен параметър – **константен указател към инстанцията/обекта**.

**Константни член-функции**:

- **Не променят член-данните (състоянието)** на структурата/класа.
- Обозначават се чрез записване на ключовата дума **const**  в декларацията и в края на заглавието в дефиницията им.
- Могат да се извикват от **константни обекти**.

```c++
struct DynamicArray
{
	int* data;
	size_t used;
	size_t allocated;

	void initialise() // inline function
	{
		data = nullptr;
		used = 0;
		allocated = 0;
	}
	void allocate(size_t size)
	{
		data = new int[size];
		used = 0;
		allocated = size;
	}
	void free()
	{
		delete[] data;
		data = nullptr;
		used = 0;
		allocated = 0;
	}

	void push_back(int el)
	{
		if (used >= allocated)
		{
	    		// resize(allocated * 2);
		}
		data[used++] = el;
	}
	int get(unsigned int index) const
	{
		assert(index < used);
		return data[index];
	}
};

int main()
{
	DynamicArray da;
	da.initialise();
	da.allocate(8);
	da.push_back(5);
	da.get(0);
}
```

:bangbang: Инстанция на структурата DynamicArray заема място в паметта колкото за три променливи (data, used, allocated) :bangbang:  
Функциите живеят като глобални (**само на едно място**).  

Всяка член-функция, скрито от нас, получава като аргумент специална променлива (**this**) – **константен указател към текущия обект, с който функцията работи**.  
Можем да си мислим, че нещата изглеждат така:  
(Долният програмен фрагмент няма да се компилира! Той е за нашата интуиция !!)  
```c++
{
	// ...
	void initialise(DynamicArray* const this)
	{
		this->data = nullptr;
		this->used = 0;
		this->allocated = 0;
	}
	int get(const DynamicArray* const this, unsigned int index)
	{
		assert(index < used);
		return data[index];
	}
	// ...
};
	
int main()
{
	DynamicArray da;
	DynamicArray::initialise(&da);
	DynamicArray::get(&da, 0);
	// ...
}
```

---

## Конструктори и деструктор

Бихме искали **инициализирането** на обект и **освобождаването на динамично заделена** памет да се извършват "автоматично", а не ние да извикваме поотделно двете функции (с цел да се избегнат грешки).  

Всяка структура/клас може да има n на брой конструктори и **само един** деструктор.  
Това са специални функции, които компилаторът ще извика автоматично вместо нас.  

**Жизнен цикъл на обект**:  
- Създаване на обект в даден scope – заделя се памет и член-данните се инициализират.
- Достига се до края на блока.
- Обектът и паметта, която е асоциирана с него, се разрушават.

**Конструктор**:  
- Извиква се веднъж – **при създаването на обекта**.
- **Не се оказва експлицитно тип на връщане**.
- Има **същото име като класа**.

**Деструктор**:  
- Извиква се веднъж – **при изтриването на обекта**.
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
	
	void push_back(int el)
	{
		if (used >= allocated)
		{
	    		// resize(allocated * 2);
		}
		data[used++] = el;
	}
	int get(unsigned int index) const
	{
		assert(index < used);
		return data[index];
	}
};

int main()
{
	DynamicArray da; // DynamicArray::DynamicArray()
} // DynamicArray::~DynamicArray()
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

	void push_back(int el)
	{
		if (used >= allocated)
		{
	    		// resize(allocated * 2);
		}
		data[used++] = el;
	}
	int get(unsigned int index) const
	{
		assert(index < used);
		return data[index];
	}
};

int main()
{
	DynamicArray da(8); // DynamicArray::DynamicArray(8)
} // DynamicArray::~DynamicArray()
```

## Ред на работа на конструктурите и деструктурите

```c++
struct A
{
	int a;

	A()
	{
		std::cout << "A()" << std::endl;
	}
	~A()
	{
		std::cout << "~A()" << std::endl;
	}
};

struct B
{
	int b;

	B()
	{
		std::cout << "B()" << std::endl;
	}
	~B()
	{
		std::cout << "~B()" << std::endl;
	}
};

struct C
{
	A a;
	B b;
	int c;

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
struct A
{
	int a;

	A(int value) : a(value * 2) 
	{}
};

struct B
{
	int b;

	B(int value) : b(value / 2)
	{}
};

struct X
{
	A a;
	B b;
	int c;

	X(int value) : a(value), b(value), c(value * 5) // Call A(value) and B(value)
	{}
};

int main()
{
	X obj(23);
}
```
