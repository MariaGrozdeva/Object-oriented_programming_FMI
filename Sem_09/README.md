## Масиви от указатели към обекти

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_09/images/ArrayOfPointers.png)

**Задача:** Да се реализира клас SortedStringPool, представляващ сортирана колекция от низове с ограничена дължина (< 64). Класът трябва да съдържа методи за добавяне, премахване и търсене на дума като търсенето трябва да бъде с логаритмична сложност.  

---

# Move семантики

### lvalue и rvalue

**lvalue** – обект, който заема някакво конкретно място в паметта.  
**rvalue** – временен обект (някакъв израз) с временен адрес (регистър). Унищожава се "почти веднага" след като е създаден (в края на израза, в който е бил създаден).  

**&** – за **lvalue**  
**Пример:**  
```c++
#include <iostream>

bool f(int& n)
{
	return n % 2 == 0;
}
int main()
{
	int n = 10;
	f(n); // OK! n is lvalue
	f(5); // Error! 5 is not an lvalue
}
```

**&&** – за **rvalue**  
**Пример:**  
```c++
bool f(int&& n)
{
	return n % 2 == 0;
}
int main()
{
	int n = 10;
	f(n); // Error! n is not an rvalue
	f(5); // OK! 5 is rvalue
}
```

Да разгледаме следния програмен фрагмент:
```c++
MyString createString(const char* str)
{
	MyString createdString(str);
	return createdString;
}

int main()
{
	MyString str("Algebra");
	str = createString("OOP");
}
```
Резултат от изпълнението:

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_09/images/WithoutMove.png)

**Проблем:** Правим излишни копия :bangbang: Обектът, създаден в createString **се копира два пъти преди да се присвои** на str.

## Move конструктор и move оператор=
```c++
MyString::MyString(MyString&& other) noexcept
{
	str = other.str;
	size = other.size;
	other.str = nullptr;
	other.size = 0;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		
		str = other.str;
		size = other.size;
		other.str = nullptr;
		other.size = 0;
	}
	return *this;
}
```
Резултат от изпълнението на по- горния програмен фрагмент:

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_09/images/WithMove.png)

---

### Важно ❗
Всъщност, резултатът от изпълнението на фрагмента най- вероятно няма да бъде нито един от посочените, а ще бъде:  

![alt_text](https://github.com/MariaGrozdeva/Object-oriented_programming_FMI/blob/main/Sem_09/images/RVO.png)

Това се дължи на оптимизация на компилаторите, наречена **return value optimization (RVO)**.  
https://en.cppreference.com/w/cpp/language/copy_elision

---

Допълнителни материали:  
https://en.cppreference.com/w/cpp/language/value_category  
https://www.internalpointers.com/post/understanding-meaning-lvalues-and-rvalues-c  
https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners  
