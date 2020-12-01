//#include "DLList.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "DLList.h"
#include <iostream>

TEST_CASE("Operator + and += for T data (adding in front)")
{
    DLList<int> list;
    list += 1;
    list += 2;
    list += 3;
    list += 4;
    list += 5;
    list += 0;

    DLList<int> list2 = list + 3;
    CHECK(list.length() == 6);
    CHECK(list2.length() == 7);

    list.print();
    std::cout << '\n';
    list2.print();
}

TEST_CASE("Copy constructor")
{
    //DLList<int> symetry = DLList<int>::range(-3, 3);
    DLList<int> symetry;
    symetry.push_back(-2);
    symetry.push_back(-1);
    symetry.push_back(0);
    symetry.push_back(1);
    symetry.push_back(2);
    auto symetry_cpy = symetry;
    symetry_cpy += -4;
    symetry.print();
    symetry_cpy.print();
}

TEST_CASE("Insert/Push back/Delete")
{
    DLList<int> list;
    list += 3;
    list += 10;
    list.insertAt(5, 0);
    list.push_back(11);
    list.push_back(12);
    list.insertAt(25, 2);
    list.insertAt(33, list.length() - 1);
    CHECK(list.length() == 7);
    list.print();
}

TEST_CASE("Reverse")
{
    DLList<int> symetry; // = DLList<int>::range(-3, 3);
    symetry.push_back(-2);
    symetry.push_back(-1);
    symetry.push_back(0);
    symetry.push_back(1);
    symetry.push_back(2);
    symetry.reverse();
    symetry.print();
}

TEST_CASE("Swap and unique")
{
    DLList<int> symetry; // = DLList<int>::range(-3, 3);
    symetry.push_back(-2);
    symetry.push_back(-1);
    symetry.push_back(0);
    symetry.push_back(1);
    symetry.push_back(2);
    symetry.swap(0, 4);
    symetry.print();

    symetry.insertAt(-3, 0);
    symetry += 3;
    //symetry.unique();
    symetry.print();
}

TEST_CASE("Create from array")
{
    int vector[] = {10, 20, 30, 40, 50};
    DLList<int> list;
    list = list.createFromArray(vector, 5);
    list.print();
}
TEST_CASE("Operator +/+= for lists")
{
    int vector[] = {10, 20, 30, 40, 50};
    DLList<int> list;
    list = list.createFromArray(vector, 5);

    int vector2[] = {3, 29, 13, 7};
    DLList<int> list2;
    list2 = list2.createFromArray(vector2, 4);

    auto list3 = list + list2;
    CHECK(list3.length() == 9);
    //list3.swap(0, 5);
    list3.print();

    list2 += list;
    list.push_back(105);
    list2.print();
}

TEST_CASE("Deleting and edge cases and reverse iteration")
{
    DLList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);     // 1, 2, 3, 4
    list.insertAt(10, 1);  // 1, 2, 10, 3, 4
    list.insertAt(-10, 0); // 1, -10, 2, 10, 3, 4
    list.print();

    list.pop(); // 1, -10, 2, 10, 3
    list.print();

    list.eraseAt(1); // 1, -10, 10, 3

    CHECK(list.length() == 4);
    list.eraseAt(2); // 1, -10, 10
    CHECK(list.length() == 3);
    list.print();

    auto reverseIt = list.preEnd();

    while (reverseIt != list.end())
    {
        std::cout << *reverseIt << ' ';
        --reverseIt;
    }
}

int main()
{

    doctest::Context().run();
    return 0;
}