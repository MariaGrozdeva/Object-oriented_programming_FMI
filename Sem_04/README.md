# Класове. Член-функции. Модификатори за достъп. Капсулация.

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
void free(DynamicArray& da)
{
	delete[] da.data;
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

int& at(DynamicArray& da, size_t index)
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
- Имената им са от вида **\<StructName\>::\<memberFunctionName\>**
- **Работят с член-данните на инстанцията/обекта** от дадена структура/клас.
- **Извикват се с инстанция/обект** на структурата/класа.
- Компилаторът преобразува всяка член-функция на дадена структура/клас в обикновена функция с уникално име и един допълнителен параметър –**указател към инстанцията/обекта**.

**Константни член-функции**:

- **Не променят член-данните** на структурата/класа.
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
	void free()
	{
		delete[] data;
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

	int& at(size_t index)
	{
		assert(index < used);
		return data[index];
	}
};

int main()
{
	DynamicArray da;
	da.initialise();
	da.allocate(100);
	da.at(5) = 22;
}
```

:bangbang: Инстанция на структурата DynamicArray заема място в паметта колкото за три променливи (data, used, allocated) :bangbang:  
Функциите живеят като глобални (**само на едно място**).  

Всяка член-функция, скрито от нас, получава като аргумент специална променлива (**this**) - **пойнтър към текущия обект, с който функцията работи**.  
Можем да си мислим, че нещата изглеждат така:  
(Долният програмен фрагмент няма да се компилира! Той е за нашата интуиция !!)  
```c++
{
	// ...
	void initialise(DynamicArray* this)
	{
		this->data = nullptr;
		this->used = 0;
		this->allocated = 0;
	}
	// ...
};
	
int main()
{
	DynamicArray da;
	DynamicArray::initialise(&da);
	// ...
}
```

Сега, искаме "външният свят" да **няма достъп до всички член-данни и методи на даден клас**. Това е така, защото тяхната промяна може да доведе до неочаквано поведение на нашата програма. Как можем да го постигнем?  

# Капсулация (encapsulation) - първи принцип на Обектно-ориентираното програмиране

|Модификатор за достъп|Предназначение|  
|--|--|  
|private|Атрибутите, попадащи в обхвата на този модификатор, са вътрешни за съответния клас (не могат да се използват от "външния свят").|  
|protected|Като private + съответните атрибути могат да се използват и от наследниците на класа.|  
|public|Атрибутите, попадащи в обхвата на този модификатор, са видими и за "външния свят").|  

:bangbang: **Разлика между структура и клас**  
По подразбиране всички член данни и методи **на структурата са public-елементи**, а тези **на класа - private-елементи**.  
