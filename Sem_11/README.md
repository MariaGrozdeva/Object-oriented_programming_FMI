# Виртуални функции. Статично и динамично свързване

**Пример за *статично свързване*:**
```c++
class Base
{
public:
	void f() const
	{
		std::cout << "Base::f()" << std::endl;
	}
};
class Derived : public Base
{
public:
	void f() const
	{
		std::cout << "Derived::f()" << std::endl;
	}
};

int main()
{
	Derived derivedObject;

	Base* pb = &derivedObject;
	Derived* pd = &derivedObject;

	pb->f();
	pd->f();

	std::cout << "----------" << std::endl;

	Base& bref = derivedObject;
	Derived& dref = derivedObject;

	bref.f();
	dref.f();
}
```

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_11/images/StaticBindingExampleOutput.png)

**Пример за *виртуална функция* и *динамично свързване*:**
```c++
class Base
{
public:
	virtual void f() const
	{
		std::cout << "Base::f()" << std::endl;
	}
};
class Derived : public Base
{
public:
	virtual void f() const override
	{
		std::cout << "Derived::f()" << std::endl;
	}
};

int main()
{
	Derived derivedObject;

	Base* pb = &derivedObject;
	Derived* pd = &derivedObject;

	pb->f();
	pd->f();

	std::cout << "----------" << std::endl;

	Base& bref = derivedObject;
	Derived& dref = derivedObject;

	bref.f();
	dref.f();
}
```

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_11/images/DynamicBindingExampleOutput.png)

❗ **Статично свързване** - методът, който ще се извика, се определя по време на компилация и при всяко изпълнение е един и същ.  
❗ **Динамично свързване** - методът, който ще се извика, се определя по време на изпълнение на програмата.  

---

# Виртуални таблици и виртуални указатели

```c++
class Base
{
public:
	virtual void f() const
	{
		std::cout << "Base::f()" << std::endl;
	}
	virtual void g() const
	{
		std::cout << "Base::g()" << std::endl;
	}

	void nonVirtual() const
	{
		std::cout << "Base::nonVirtual()" << std::endl;
	}
};

class FirstLevel : public Base
{
public:
	virtual void f() const override
	{
		std::cout << "FirstLevel::f()" << std::endl;
	}
	virtual void g() const override
	{
		std::cout << "FirstLevel::g()" << std::endl;
	}
	virtual void h() const
	{
		std::cout << "FirstLevel::h()" << std::endl;
	}

	void nonVirtual() const
	{
		std::cout << "FirstLevel::nonVirtual()" << std::endl;
	}
};
class SecondLevel : public FirstLevel
{
public:
	virtual void f() const override
	{
		std::cout << "SecondLevel::f()" << std::endl;
	}
};
class ThirdLevel : public SecondLevel
{
public:
	virtual void h() const override
	{
		std::cout << "ThirdLevel::h()" << std::endl;
	}
};

int main()
{
	Base baseObject;
	FirstLevel firstLevelObject;
	SecondLevel secondLevelObject;
	ThirdLevel thirdLevelObject;

	Base* bp = nullptr;	

	bp = &baseObject;
	bp->f();
	bp->g();

	bp = &firstLevelObject;
	bp->f();
	bp->g();

	bp = &secondLevelObject;
	bp->f();
	bp->g();

	bp = &thirdLevelObject;
	bp->f();
	bp->g();
}
```

Виртуални таблици за създадените класове:

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_11/images/VirtualTables.png)

---

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_11/images/VtableVptr.png)

---

Извикване на виртуална функция от **конструктор/деструктор**:  

```c++
class Base
{
public:
	virtual void f() const
	{
		std::cout << "Base::f()" << std::endl;
	}

	void g() const
	{
		f();
	}
	Base()
	{
		f();
	}
	virtual ~Base()
	{
		f();
	}
};
class Derived : public Base
{
public:
	virtual void f() const override
	{
		std::cout << "Derived::f()" << std::endl;
	}
};

int main()
{
	Derived der;
	der.g();
}
```

Резултат:  

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_11/images/ConstrDestrCallingVirtualMethods.png)

 ---
 
# Полиморфизъм - четвърти принцип на ООП

Едни и същи действия се реализират по различен начин в зависимост от обектите, върху които се прилагат.
- Действията се наричат полиморфни;
- Полиморфизмът се реализира чрез виртуални функции;
- Класовете, върху които ще се прилагат полиморфни действия, трябва да имат общ родител или прародител, т.е. да са наследници на един и същи клас;
- В този общ родител се дефинира виртуален метод, съответстващ на полиморфното действие;
- Всеки клас-наследник предефинира или не виртуалния метод;
- Активирането става чрез указател/референция от базовия клас.

:bangbang::bangbang: При полиморфна йерархия ще изтриваме обектите чрез указатели от базовия клас. За да се извикват правилните деструкори, задължително **деструкторът на базовия клас** трябва е деклариран като виртуален!

**Пример за полиморфизъм:**
```c++
class Animal
{
public:
	virtual void sound() const
	{
		std::cout << "Undefined sound!" << std::endl;
	}

	virtual ~Animal() {}
};

class Dog : public Animal
{
public:
	void sound() const override
	{
		std::cout << "Bark bark" << std::endl;
	}
};
class Cat : public Animal
{
public:
	void sound() const override
	{
		std::cout << "Meow meow" << std::endl;
	}
};
class Cow : public Animal
{
public:
	void sound() const override
	{
		std::cout << "Moo moo" << std::endl;
	}
};

int main()
{
	Animal** animals = new Animal * [4];

	animals[0] = new Dog();
	animals[1] = new Cat();
	animals[2] = new Cow();
	animals[3] = new Animal();

	animals[0]->sound();
	animals[1]->sound();
	animals[2]->sound();
	animals[3]->sound(); // Undefined sound (not good - we don't want to be able to create objects of type Animal – it should just be a base for the others)

	delete animals[0], animals[1], animals[2], animals[3];
	delete[] animals;
}
```

---

# Абстрактни класове

**Чисто виртуална функция (pure virtual)** - функция, която ни освобождава от задължението да й предоставим дефиниция.  

Клас, в който има поне една чиста виртуална функция, се нарича **абстрактен клас**.  

Абстрактните класове са предназначени единствено за наследяване и не може да създаваме обекти от тях. Във всеки наследник сме задължени да разпишем дефиниция на чисто виртуалните методи. Ако някой наследник няма собствена имплементация, то и той става абстрактен клас.  

**Пример (класът Animal е абстрактен, защото методът sound() е pure virtual, както и класът Mouse, защото не е разписал дефиниция на sound()):**
```c++
class Animal
{
public:
	virtual void sound() const = 0;
	virtual ~Animal() = default;
};

class Dog : public Animal
{
public:
	void sound() const override
	{
		std::cout << "Bark bark" << std::endl;
	}
};
class Cat : public Animal
{
public:
	void sound() const override
	{
		std::cout << "Meow meow" << std::endl;
	}
};
class Cow : public Animal
{
public:
	void sound() const override
	{
		std::cout << "Moo moo" << std::endl;
	}
};

class Mouse : public Animal
{
};

int main()
{
	// Animal* pa = new Animal(); // Error! Animal is an abstract class!
	// Animal* pm = new Mouse(); // Error! Mouse is also an abstract class!

	Animal** animals = new Animal * [3];

	animals[0] = new Dog();
	animals[1] = new Cat();
	animals[2] = new Cow();

	animals[0]->sound();
	animals[1]->sound();
	animals[2]->sound();

	delete animals[0], animals[1], animals[2];
	delete[] animals;
}
```
