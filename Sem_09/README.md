# Масиви от указатели, Move семантики, lvalue/rvalue

---

## Масиви от указатели към обекти

При работа с полиморфни обекти или обекти с голям размер, често е по-ефективно да се пазят **указатели** към тях, а не самите обекти. Масив от указатели позволява:

- Полиморфно поведение (чрез базов клас)
- Избягване на копиране при преместване на елементи
- По-гъвкаво управление на живота на обектите

**Задача:** Да се реализира клас `SortedStringPool`, представляващ сортирана колекция от низове с ограничена дължина (< 64). Класът трябва да съдържа методи за добавяне, премахване и търсене на дума, като търсенето трябва да бъде с логаритмична сложност.

Понеже колекцията е сортирана, можем да използваме **двоично търсене** — O(log n). Самите низове се пазят като `char*` указатели (или `char[64]` буфери), а масивът поддържа сортираност при всяка операция.

---

# Move семантики и Value Categories

## lvalue и rvalue — Какво са?

В C++ всеки израз има два аспекта: **тип** и **value category**. Value category определя дали можем да вземем адреса на израза и колко дълго живее той.

### lvalue (left-value)

**lvalue** е израз, който обозначава обект с **конкретно, стабилно място в паметта** — т.е. обект, чийто адрес можем да вземем с `&`.

```cpp
int x = 10;      // x е lvalue — има адрес
int arr[5];      // arr[2] е lvalue
std::string s;   // s е lvalue

&x;              // OK — можем да вземем адреса
&arr[2];         // OK
```

Практическо правило: ако можеш да напишеш `&израз` без грешка от компилатора, изразът е lvalue.

### rvalue (right-value)

**rvalue** е временен обект — израз, чийто резултат **не е обвързан с конкретно място в паметта** (или е обвързан, но само временно). rvalue-тата се унищожават в края на израза, в който са създадени.

```cpp
42                   // rvalue — числов литерал
x + y                // rvalue — временен резултат
std::string("hello") // rvalue — временен обект
```

> **Важно:** В C++11 rvalue категорията се разделя допълнително на **prvalue** (pure rvalue) и **xvalue** (expiring value). За практически цели ще използваме просто "rvalue", имайки предвид и двете.

### Примери за разграничение

```cpp
int x = 10;
int y = 20;

x = 5;        // OK: x е lvalue
// 5 = x;     // Грешка: 5 е rvalue — не може да е ляво на присвояване

x + y;        // rvalue — временен резултат, не можем да вземем адреса му
// &(x + y);  // Грешка: не можем да вземем адрес на rvalue
```

---

## lvalue референции (`&`) и rvalue референции (`&&`)

### lvalue референция (`T&`)

Обвързва се **само с lvalue**:

```cpp
void f(int& n) { /* ... */ }

int x = 10;
f(x); // OK — x е lvalue
f(5); // Грешка! 5 е rvalue
```

Изключение: `const T&` може да се обвърже и с rvalue (удължава живота му):

```cpp
void g(const int& n) { /* ... */ }

g(5); // OK! const lvalue референция може да приема rvalue
```

### rvalue референция (`T&&`) — само за конкретен тип

Когато пишем `ConcreteType&&`, функцията приема **само rvalue** от точно този тип. Това е начинът да "хванем" временен обект и да му "откраднем" ресурсите.

```cpp
void h(int&& n) { /* ... */ }

int x = 10;
h(x);     // Грешка! x е lvalue, не rvalue
h(5);     // OK — 5 е rvalue
h(x + 1); // OK — x + 1 е rvalue (временен резултат)
```

**Ключово разбиране:** Параметърът `n` вътре в тялото на `h` **сам по себе си е lvalue** — той има име, има адрес. Само при извикването се изисква аргументът да е rvalue.

```cpp
void h(int&& n) {
    // n тук е lvalue! Има конкретно място в паметта.
    int* ptr = &n;  // OK
}
```

---

## Проблемът с излишното копиране

Нека разгледаме клас `MyString`:

```cpp
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

Без move семантики, при присвояването `str = createString("OOP")`:

1. `createdString` се конструира вътре в `createString`
2. При `return` — копиране (copy constructor) → нов временен обект
3. При `=` — copy assignment → данните се копират отново в `str`
4. Временните обекти се унищожават → ресурсите, които са копирани, се освобождават

Правим **излишна работа**: копираме данни само за да ги унищожим след момент.

---

## Move конструктор и Move `operator=`

Идеята е проста: вместо да **копираме** ресурсите на временен обект (rvalue), **ги "крадем"** — вземаме указателя, а оригиналния обект оставяме във валидно, но "празно" състояние.

```cpp
// Move конструктор
MyString::MyString(MyString&& other) noexcept
{
    str = other.str;   // Вземаме указателя
    size = other.size;

    other.str = nullptr; // Оставяме във валидно, но празно състояние
    other.size = 0;
}

// Move присвояване
MyString& MyString::operator=(MyString&& other) noexcept
{
    if (this != &other)
    {
        free(); // Освобождаваме собствените си ресурси

        str = other.str;
        size = other.size;

        other.str = nullptr;
        other.size = 0;
    }
    return *this;
}
```

### Кога се извиква move конструкторът?

Компилаторът автоматично избира move конструктора когато аргументът е **rvalue** — т.е. временен обект, който "скоро ще умре":

```cpp
MyString a("hello");
MyString b = std::move(a);          // Явно — move constructor
MyString c = createString("world"); // Неявно — return стойността е rvalue
```

### noexcept — Защо е важно?

Маркирането с `noexcept` е критично за производителност. STL контейнерите (напр. `std::vector`) ще използват move вместо copy при преоразмеряване **само ако** move операцията е `noexcept`. Ако не е, те се връщат към копирането за гарантиране на exception safety.

---

## `std::move` — Само каст, нищо повече!

> **Критично разбиране:** `std::move` **не мести нищо**. Не прави никаква работа по време на изпълнение. Той е просто **static_cast към rvalue референция**.

```cpp
// std::move прави ТОЧНО ТОВА:
template<typename T>
constexpr std::remove_reference_t<T>&& move(T&& t) noexcept
{
    return static_cast<std::remove_reference_t<T>&&>(t);
}
```

Единствената му цел е да каже на компилатора: *"Третирай този обект като rvalue — разрешавам ресурсите му да бъдат взети."*

```cpp
MyString a("hello");
MyString b = std::move(a);
// std::move(a) е просто static_cast<MyString&&>(a)
// Самото "местене" се извършва от move конструктора на MyString
```

### Внимание след `std::move`!

След `std::move(a)`, обектът `a` е във **валидно, но неопределено** (moved-from) състояние. Не трябва да го използваме без предварително присвояване:

```cpp
MyString a("hello");
MyString b = std::move(a);

// a.data() може да е nullptr сега!
// Единственото безопасно нещо е да присвоим нова стойност:
a = MyString("world"); // OK
```

---

## Universal References (Forwarding References) — `T&&`

Тук идва важно разграничение. Когато пишем `T&&` в **шаблонен контекст**, това **не е** задължително rvalue референция — това е т.нар. **универсална/препращаща референция** (universal/forwarding reference).

### Разграничение:

| Синтаксис | В какъв контекст | Какво е? |
|---|---|---|
| `ConcreteType&&` | Навсякъде | rvalue референция — приема **само rvalue** |
| `T&&` | Шаблонна функция с `T` deduced | Universal reference — приема **и lvalue, и rvalue** |
| `auto&&` | `auto` deduction | Universal reference |

```cpp
// rvalue референция — САМО rvalue:
void f(MyString&& s);

// Universal reference — ВСИЧКО:
template<typename T>
void g(T&& x);
```

### Reference Collapsing (Свиване на референции)

Когато `T` се дедуцира, важат правилата за **reference collapsing**:

| Тип на аргумента | `T` се дедуцира като | `T&&` става |
|---|---|---|
| lvalue `int` | `int&` | `int& &&` → `int&` |
| rvalue `int` | `int` | `int&&` |
| lvalue `string` | `string&` | `string& &&` → `string&` |
| rvalue `string` | `string` | `string&&` |

Правилото е просто: **`& &&` → `&`** (ако има поне една `&`, резултатът е lvalue референция).

```cpp
template<typename T>
void g(T&& x) {
    // Ако извикаме g(lvalue) → T = int&, x е int&
    // Ако извикаме g(rvalue) → T = int,  x е int&&
}

int n = 5;
g(n);            // T = int&, x е int& (lvalue ref)
g(5);            // T = int,  x е int&& (rvalue ref)
g(std::move(n)); // T = int,  x е int&&
```

---

## `std::forward` — Перфектно препращане

`std::forward`, също като `std::move`, **не прави нищо по време на изпълнение**. Той е **условен каст** — каства към rvalue само ако аргументът е бил rvalue при извикването.

```cpp
// std::forward прави ТОЧНО ТОВА:
template<typename T>
constexpr T&& forward(std::remove_reference_t<T>& t) noexcept
{
    return static_cast<T&&>(t);
}
```

### Защо ни трябва?

Проблемът: вътре в шаблонна функция, параметърът `x` (дори ако е `T&&`) **е lvalue** — има име, има адрес. Ако го предадем нататък, ще го предадем като lvalue, губейки информацията дали оригиналът е бил rvalue.

```cpp
template<typename T>
void wrapper(T&& x) {
    // x ТУК е lvalue (има име)!
    target(x);                  // Винаги предава lvalue → ГРЕШНО
    target(std::move(x));       // Винаги предава rvalue → ГРЕШНО (губим lvalue случая)
    target(std::forward<T>(x)); // Предава lvalue ако T=int&, rvalue ако T=int → ПРАВИЛНО
}
```

### Пълен пример — `make_unique`-подобна функция:

```cpp
template<typename T, typename... Args>
std::unique_ptr<T> my_make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// При извикване:
auto p1 = my_make_unique<MyString>("hello");      // "hello" е rvalue → forward като rvalue
std::string s = "world";
auto p2 = my_make_unique<MyString>(s);            // s е lvalue       → forward като lvalue
auto p3 = my_make_unique<MyString>(std::move(s)); // move(s) е rvalue → forward като rvalue
```

Без `std::forward`, конструкторът на `T` би получавал само lvalue, дори когато оригиналният аргумент е бил rvalue — губим предимствата на move семантиките.

### Обобщение: `std::move` vs `std::forward`

| | `std::move(x)` | `std::forward<T>(x)` |
|---|---|---|
| **Runtime работа** | Нищо — само каст | Нищо — само каст |
| **Каства към** | Винаги `rvalue&&` | `rvalue&&` ако T=U, `lvalue&` ако T=U& |
| **Кога се ползва** | Когато искаме да "подарим" ресурсите на обект | В шаблони с universal references за перфектно препращане |
| **Безопасно ли е след употреба?** | Обектът е в moved-from състояние | Зависи от случая |

---

## Return Value Optimization (RVO)

В реалността, горният пример с `createString` вероятно **изобщо няма да извика** нито copy, нито move конструктор. Компилаторите прилагат оптимизация наречена **Return Value Optimization (RVO)** / **Named Return Value Optimization (NRVO)**.

При RVO, компилаторът директно конструира обекта на мястото на дестинацията — т.е. конструира `createdString` директно в паметта, предназначена за `str`. Никакво копиране или местене не се случва.

От C++17, **copy elision при prvalue** е **гарантирано** от стандарта (mandatory elision), а NRVO остава незадължително, но всички основни компилатори го прилагат.

```cpp
MyString createString(const char* s) {
    return MyString(s); // prvalue → гарантирано RVO от C++17
}

MyString createString2(const char* s) {
    MyString result(s);
    return result; // NRVO — компилаторите обикновено го оптимизират, но не е гарантирано
}
```

> **Практически извод:** Не разчитай на RVO за коректност на кода, но го имай предвид при анализ на производителността. Пиши move конструктори — те са fallback когато RVO не може да се приложи.

---

## Rule of Five

Ако дефинираш поне едно от следните, трябва да дефинираш всичките пет:

1. Деструктор
2. Copy конструктор
3. Copy `operator=`
4. **Move конструктор** ← ново в C++11
5. **Move `operator=`** ← ново в C++11

```cpp
class MyString {
public:
    MyString(const char* s);                        // Конструктор
    ~MyString();                                    // 1. Деструктор
    MyString(const MyString& other);                // 2. Copy constructor
    MyString& operator=(const MyString& other);     // 3. Copy assignment
    MyString(MyString&& other) noexcept;            // 4. Move constructor
    MyString& operator=(MyString&& other) noexcept; // 5. Move assignment
};
```

---

## Допълнителни материали

- [cppreference — Value categories](https://en.cppreference.com/w/cpp/language/value_category)
- [cppreference — Copy elision / RVO](https://en.cppreference.com/w/cpp/language/copy_elision)
- [cppreference — std::move](https://en.cppreference.com/w/cpp/utility/move)
- [cppreference — std::forward](https://en.cppreference.com/w/cpp/utility/forward)
- [Understanding lvalues and rvalues](https://www.internalpointers.com/post/understanding-meaning-lvalues-and-rvalues-c)
- [C++ rvalue references and move semantics for beginners](https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners)
