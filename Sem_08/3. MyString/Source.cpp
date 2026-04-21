#include "MyString.h"
#include <iostream>

int main()
{
    MyString s1("Hello");
    MyString s2("World");
    MyString s3;

    std::cout << "s1: " << s1 << "\n";
    std::cout << "s2: " << s2 << "\n";
    std::cout << "s3 (empty), size: " << s3.getSize() << "\n\n";

    // ─── copy constructor ────────────────────────────────────────────────────

    MyString s4(s1);
    std::cout << "s4 (copy of s1): " << s4 << "\n\n";

    // ─── assignment ──────────────────────────────────────────────────────────

    MyString s5;
    s5 = s2;
    std::cout << "s5 (assigned from s2): " << s5 << "\n";

    // self-assignment — should be a no-op
    s5 = s5;
    std::cout << "s5 after self-assign: " << s5 << "\n\n";

    // ─── operator+= ──────────────────────────────────────────────────────────

    MyString s6("Hello");
    s6 += MyString(", World!");
    std::cout << "s6 after +=: " << s6 << "\n";
    std::cout << "s6 size: " << s6.getSize() << "\n\n";

    // ─── operator+ ───────────────────────────────────────────────────────────

    MyString s7 = s1 + MyString(", ") + s2;
    std::cout << "s7 (s1 + \", \" + s2): " << s7 << "\n\n";

    // ─── comparisons ─────────────────────────────────────────────────────────

    MyString a("apple");
    MyString b("banana");
    MyString c("apple");

    std::cout << "a == c : " << (a == c) << "\n";
    std::cout << "a != b : " << (a != b) << "\n";
    std::cout << "a <  b : " << (a <  b) << "\n";
    std::cout << "b >  a : " << (b >  a) << "\n";
    std::cout << "a <= c : " << (a <= c) << "\n";
    std::cout << "b >= a : " << (b >= a) << "\n\n";

    // ─── operator>> ──────────────────────────────────────────────────────────

    std::cout << "Enter a word: ";
    MyString input;
    std::cin >> input;
    std::cout << "You entered: " << input << " (size: " << input.getSize() << ")\n\n";

    return 0;
}
