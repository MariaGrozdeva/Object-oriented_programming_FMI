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
