# Голямата четворка (Big 4)

- Конструктор по подразбиране (Default constructor)
- Конструктор за копиране (Copy constructor)
- Оператор= (Copy assignment operator)
- Деструктор (Destructor)

Да разгледаме следната структура:
```c++
struct Test
{
	int valueX;
	int valueY;
};
```
Понеже функциите от голямата четворка не са дефинирани в структурата, компилаторът ще създаде такива.  
**Пример:**
```c++
int main()
{
	Test a, b; // Default constructors for a and b
	Test c(a); // Default copy constructor for c (c.valueX = a.valueX, c.valueY = a.valueY is what the compiler does)
	a = b;     // Default copy assignment operator for a
}                  // Default destructors for a, b and c
```
Кодът се компилира успешно и функциите имат правилно поведение.

### Как работят дефинираните от компилатора функции от голямата четворка?

Всяка една от тези функции **извиква същите функции върху член-данните.**
```c++
struct Test
{	
	A obj1;
	B obj2;
	C obj3;
};
```

#### Пример за конструктора по подразбиране:
![alt_text](https://i.ibb.co/N7br0ZX/default-Constr.png)

#### Пример за деструктора:
![alt_text](https://i.ibb.co/t3rCZFK/default-Destr.png)

#### Пример за копиращия конструктор:
![alt_text](https://i.ibb.co/mCBdWRt/copy-Constr.png)

### Проблем при функциите, генерирани от компилатора:
Да разгледаме следния код:
```c++
class Person
{
private:
    char* name;
    size_t age;

public:
    Person(const char* name, int age)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->age = age;
    }
};

int main()
{
    Person p1;
    Person p2(p1);
}
```
Копиращият конструктор, създаден от компилатора, има **неправилно поведение**. :x:

Създаденото копие се нарича **shallow copy**. В p2 **сме копирали указателя, а не самото име** на p1, което води до споделяне на обща динамична памет. В тази ситуация **трябва да се имплементират експлицитно** ***копиращия конструктор***, ***оператора за присвояване*** и ***деструктора***, защото генерираните от компилатора не работят правилно.

![alt_text](https://i.ibb.co/DKJcjtk/shallow-Copy.png)

**Правилното поведение** на копиращия конструктор е следното: :heavy_check_mark:

![alt_text](https://i.ibb.co/LCcJDLx/right-Copy.png)

### Собствена имплементация на голямата четворка
```c++
// ...

Person::Person()
{}
Person::Person(const Person& other)
{
	copyFrom(other);
}
Person& Person::operator=(const Person& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Person::~Person()
{
	free();
}

void Person::copyFrom(const Person& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	age = other.age;
}
void Person::free()
{
	delete[] name;
}

// ...
```
