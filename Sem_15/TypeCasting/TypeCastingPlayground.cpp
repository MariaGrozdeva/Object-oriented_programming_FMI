#include <iostream>

struct Base { virtual void func() {} };
struct A : Base {};
struct B : Base {};

struct NonPolymorphicBase {};
struct X : NonPolymorphicBase {};

void f(Base* ptr)
{}

void g(const char* str)
{
    char* str2 = const_cast<char*>(str);
    str2[0] = 'R';
    std::cout << str2;
}

void h(const Base& obj)
{
    // obj.func(); // error! obj is const, func is NOT
    Base& ref = const_cast<Base&>(obj);
    ref.func(); // ok
}

int main()
{
    //////////////////// Type casting

    { ////////// static_cast - не прави runtime check. Използваме, когато сме сигурни към какъв тип преобразуваме.
        int a = 5;
        double b = a;
        double c = static_cast<double>(a); // еквивалентно на горното
        
        A aObj;
        f(&aObj);
        f(static_cast<Base*>(&aObj)); // еквивалентно на горното
        
        A* aPtr = new A();
        // B* bPtr = static_cast<B*>(aPtr); // error!
        
        Base* basePtr = new Base();
        delete aPtr;
        aPtr = static_cast<A*>(basePtr); // работи, защото няма runtime check
        // Какво става, ако от aPtr извикаме функция, която е дефинирана само в А ???
        delete basePtr;
    }
    
    { ////////// dynamic_cast - прави runtime check. По- бавно е. Използваме, когато не сме сигурни за типа.
        Base* basePtr = new Base();
        A* aPtr = dynamic_cast<A*>(basePtr);
        std::cout << (aPtr == nullptr) << std::endl; // 1
        delete basePtr;
        
        aPtr = new A();
        B* bPtr = dynamic_cast<B*>(aPtr);
        std::cout << (bPtr == nullptr) << std::endl; // 1
        delete aPtr;
        
        // Най- често го използваме за downcasting (от базов клас към наследник).
        basePtr = new A();
        if (A* ptr = dynamic_cast<A*>(basePtr))
        {
            // logic for A
        }
        
        // Ако използваме референции трябва задължително преобразуването да бъде в try-catch блок (при неуспех dynamic_cast ще хвърли bad_cast).
        try {
            A& ref = dynamic_cast<A&>(*basePtr);
        } catch (const std::bad_cast& e) {
            // handling of exc
        }
        delete basePtr;
        
        // Downcast-ът не винаги работи! Трябва да има поне една виртуална функция в базовия клас!
        NonPolymorphicBase* base = new X();
        // if (dynamic_cast<X*>(base)) {} // error!
        delete base;
    }
    
    { ////////// const_cast - можем да манипулираме константността на обекти като ги достъпваме чрез указатели или референции.
        // ГРЕШНО - недефинирано поведение: оригиналният обект е истински константен
        // const char str[] = "test";
        // g(str); // UB! записваме в истински константен обект
        
        // ПРАВИЛНО - оригиналният обект не е константен, просто е подаден като const
        char str[] = "test"; // не е константен!
        g(str); // безопасно - оригиналният обект е променлив
        
        Base* basePtr = new Base();
        h(*basePtr); // безопасно - basePtr не е константен, h() просто приема const референция
        
        delete basePtr;
    }
    
    { ////////// reinterpret_cast - преобразуваме указател от произволен тип към указател от произволен тип.
        A* aPtr = new A();
        B* bPtr = reinterpret_cast<B*>(aPtr); // ok
        delete aPtr;
    }
}
