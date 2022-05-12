# Шаблони (templates)

**Какво е шаблон?**  
Функция или клас, която/който работи не с променливи от някакъв дефиниран тип, а с абстрактни променливи, се нарича шаблонна функция/клас.  

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

:bangbang: Не можем да разделяме шаблонни класове в .h и .cpp файлове. **Трябва да пишем декларацията и дефиницията им в един файл** - например .hpp файл. Причината е следната:  

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
Следователно компилаторът трябва да има достъп до дефинициите на функциите, за да може да ги инстанцира с конкретния тип (в случая - int). Ако тези дефиниции са в отделен .cpp файл, компилаторът няма да има достъп до тях и няма да може да ги инстанцира.

# Наследяване (inheritance) - трети принцип на ООП

При създаване на нов клас, който има общи компоненти и поведение с вече дефиниран клас, вместо новият клас да дефинира повторно тези компоненти и поведение, можем да го обявим за наследник на вече съществуващия и да ползваме функционалността на последния.  

**Пример** за наследяване:
```c++
class Person
{
private:
	char* name;
	size_t age;

	// ...

public:
	void setName(const char* name);
	void setAge(size_t age);

	const char* getName() const;
	size_t getAge() const;

	// ...
};

class Student : public Person
{
private:
	size_t fn;

public:
	void setFn(size_t fn);
	size_t getFn() const;
};
```

Класът-наследник (Student):
- съдържа всички член-данни и методи на основните класове (Person);
- получава достъп до **някои** от наследените компоненти на основните класове (Person).

![alt_text](https://i.ibb.co/PGKjkx3/st.png)

След като Student е наследник на Person, то при създаване на обект от тип Student се създава обект от тип Person, **който е част от обекта** от тип Student.

![al_text](https://i.ibb.co/z40DsMx/Inheritance.png)

## Видове наследяване

- private (по подразбиране)
- protected
- public

```c++
class A
{
public:
    int x;
protected:
    int y;
private:
    int z;
};

class B : public A
{
    // x is public
    // y is protected
    // z is not accessible from B
};

class C : protected A
{
    // x is protected
    // y is protected
    // z is not accessible from C
};

class D : private A
{
    // x is private
    // y is private
    // z is not accessible from D
};
```

( **Втора разлика между класове и структури:** Наследяването **при класове е private** по подразбиране, а **при структури - public** по подразбиране. )

## Подаване на базови класове и класове-наследници като параметри на функции

```c++
class A
{
public:
    int a;
};
class B : public A
{
public:
    int b;
};

void f(A& obj)
{
    obj.a++;
}
void g(B& obj)
{
    obj.b++;
}

int main()
{
    A obj1;
    B obj2;

    f(obj1); // OK!
    f(obj2); // OK!

    g(obj2); // OK!
    // g(obj1); // Error!
}
```

**Извод:** Класове-наследници **могат** да бъдат подавани като параметри на функции, които приемат обекти от базовия клас. Обратното е незвъзможно :bangbang:  

Същите правила важат, ако функциите приемат **A\* obj**/**B\* obj**.

## Конструктори и деструктори при наследяване

- Във всеки конструктор на класа-наследник трябва да се оказва кой конструктор да се извика на базовия клас. Ако не е оказано, ще се извика конструкторът по подразбиране на базовия клас **(такъв трябва да има!**).

```c++
class B : public A
{
private:
	// ...

public:
	B(...) : A(...) // constructor of A
	{
		// initialize ONLY the data members which are specific for B
	}
};
```

- Деструкторът на наследния клас извиква деструктора на базовия клас. **Първо се трият данните на класа-родител, после на класа-наследник**!

## Копиране при наследяване

При разписване на конструктора за копиране и оператора за присовяване на клас-наследник трябва експлицитно да извикваме съответно копиращия конструктор и оператора за присвояване на базовия клас.

```c++
B::B(const B& other) : A(other) // copy constructor of A
{
    copyFrom(other);
}

B& B::operator=(const B& other)
{
    if (this != &other)
    {
        A::operator=(other); // operator= of A

        free();
        copyFrom(other);
    }
    return *this;
}
```

Разписваме копирането и триенето **само ако наследникът ползва необработена динамична памет** :bangbang:
