#include "SortedStringPool.h"
#include <iostream>
#include <cassert>

static int testsRun = 0;
static int testsPassed = 0;

static void check(bool condition, const char* label)
{
    testsRun++;
    if (condition)
    {
        std::cout << "  [PASS] " << label << "\n";
        testsPassed++;
    }
    else
    {
        std::cout << "  [FAIL] " << label << "\n";
    }
}

static void section(const char* title)
{
    std::cout << "\n=== " << title << " ===\n";
}

static void testBasicAdd()
{
    section("Basic add and sorted order");
    SortedStringPool pool;

    pool.add("banana");
    pool.add("apple");
    pool.add("cherry");

    check(strcmp(pool[0], "apple") == 0, "pool[0] == apple");
    check(strcmp(pool[1], "banana") == 0, "pool[1] == banana");
    check(strcmp(pool[2], "cherry") == 0, "pool[2] == cherry");
}

static void testAddDuplicates()
{
    section("Duplicate sharing (refCount)");
    SortedStringPool pool;

    pool.add("dog");
    pool.add("cat");
    pool.add("dog");

    check(strcmp(pool[0], "cat") == 0, "pool[0] == cat");
    check(strcmp(pool[1], "dog") == 0, "pool[1] == dog");
    check(strcmp(pool[2], "dog") == 0, "pool[2] == dog");

    pool.removeAt(1);
    check(strcmp(pool[0], "cat") == 0, "after removeAt(1): pool[0] == cat");
    check(strcmp(pool[1], "dog") == 0, "after removeAt(1): pool[1] == dog (survivor)");
}

static void testContains()
{
    section("contains()");
    SortedStringPool pool;

    pool.add("mango");
    pool.add("apple");
    pool.add("mango");
    pool.add("banana");

    check(pool.contains("apple") == 0, "contains apple -> index 0");
    check(pool.contains("banana") == 1, "contains banana -> index 1");
    check(pool.contains("mango") == 2, "contains mango -> first occurrence index 2");
    check(pool.contains("grape") == -1, "contains grape -> -1 (not found)");
}

static void testRemoveAt()
{
    section("removeAt()");
    SortedStringPool pool;

    pool.add("alpha");
    pool.add("beta");
    pool.add("gamma");

    check(pool.removeAt(1), "removeAt(1) returns true");
    check(strcmp(pool[0], "alpha") == 0, "pool[0] == alpha");
    check(strcmp(pool[1], "gamma") == 0, "pool[1] == gamma");
    check(!pool.removeAt(99), "removeAt(99) returns false");
}

static void testCopyConstructor()
{
    section("Copy constructor");
    SortedStringPool original;
    original.add("x");
    original.add("y");
    original.add("x");

    SortedStringPool copy(original);

    check(strcmp(copy[0], "x") == 0, "copy[0] == x");
    check(strcmp(copy[1], "x") == 0, "copy[1] == x");
    check(strcmp(copy[2], "y") == 0, "copy[2] == y");

    copy.removeAt(0);
    check(strcmp(original[0], "x") == 0, "original[0] still == x after copy mutation");
}

static void testAssignmentOperator()
{
    section("Assignment operator");
    SortedStringPool a;
    a.add("foo");
    a.add("bar");

    SortedStringPool b;
    b.add("zzz");
    b = a;

    check(strcmp(b[0], "bar") == 0, "b[0] == bar after assignment");
    check(strcmp(b[1], "foo") == 0, "b[1] == foo after assignment");

    b = b;
    check(strcmp(b[0], "bar") == 0, "b[0] == bar after self-assignment");
}

static void testTooLongString()
{
    section("String too long");
    SortedStringPool pool;

    char tooLong[65];
    for (int i = 0; i < 64; i++)
    {
        tooLong[i] = 'a';
    }
    tooLong[64] = '\0';

    check(!pool.add(tooLong), "add() returns false for 64-char string");
}

static void testResizeTrigger()
{
    section("Resize (capacity growth)");
    SortedStringPool pool;

    pool.add("a");
    pool.add("b");
    pool.add("c");
    pool.add("d");
    pool.add("e");

    check(strcmp(pool[0], "a") == 0, "pool[0] == a after resize");
    check(strcmp(pool[4], "e") == 0, "pool[4] == e after resize");
}

static void testPrintOperator()
{
    section("operator<<");
    SortedStringPool pool;

    pool.add("zebra");
    pool.add("ant");
    pool.add("bee");

    std::cout << "  Output: " << pool << "\n";
    check(true, "operator<< did not crash");
}

static void testMultipleDuplicates()
{
    section("Multiple distinct duplicates");
    SortedStringPool pool;

    pool.add("b");
    pool.add("a");
    pool.add("b");
    pool.add("a");
    pool.add("c");
    pool.add("a");

    check(strcmp(pool[0], "a") == 0, "pool[0] == a");
    check(strcmp(pool[1], "a") == 0, "pool[1] == a");
    check(strcmp(pool[2], "a") == 0, "pool[2] == a");
    check(strcmp(pool[3], "b") == 0, "pool[3] == b");
    check(strcmp(pool[4], "b") == 0, "pool[4] == b");
    check(strcmp(pool[5], "c") == 0, "pool[5] == c");
    check(pool.contains("a") == 0, "contains a -> 0 (first)");
    check(pool.contains("b") == 3, "contains b -> 3 (first)");
}

static void testRemoveDuplicatesFully()
{
    section("Remove all copies of a duplicate");
    SortedStringPool pool;

    pool.add("hello");
    pool.add("hello");
    pool.add("world");

    pool.removeAt(0);
    pool.removeAt(0);

    check(strcmp(pool[0], "world") == 0, "only world remains");
    check(pool.contains("hello") == -1, "hello no longer found");
}

int main()
{
    std::cout << "SortedStringPool - test suite\n";

    testBasicAdd();
    testAddDuplicates();
    testContains();
    testRemoveAt();
    testCopyConstructor();
    testAssignmentOperator();
    testTooLongString();
    testResizeTrigger();
    testPrintOperator();
    testMultipleDuplicates();
    testRemoveDuplicatesFully();

    std::cout << "\n--- Results: " << testsPassed << " / " << testsRun << " passed ---\n";

    return (testsPassed == testsRun) ? 0 : 1;
}
