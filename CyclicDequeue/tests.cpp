#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "deque.h"

TEST_CASE("resizes")
{
    Deque<int> d(4);
    CHECK(d.length() == 0);
    CHECK(d.capacity() == 8);

    for (int i = 0; i < 4; i++)
        d.push_front(i);

    CHECK(d.length() == 4);
    CHECK(d.capacity() == 8);

    d.push_back(10);
    CHECK(d.length() == 5);
    CHECK(d.capacity() == 8);
    CHECK(d[4] == 10);

    d.pop_back();
    d.pop_back();
    CHECK(d.length() == 3);
    CHECK(d[2] == 1);

    d.pop_front();
    d.pop_front();
    CHECK(d.length() == 1);
    CHECK(d[0] == 1);

    d.pop_front();
    CHECK(d.length() == 0);

    for (int i = 0; i < 17; i++)
        d.push_back(i);

    CHECK(d.length() == 17);
    CHECK(d.capacity() == 32);
    CHECK(d[16] == 16);
}

TEST_CASE("removes_at1")
{
    Deque<int> d(5);
    int i = 0;
    while (i < 5)
    {
        d.push_back(i);
        i++;
    }
    CHECK(d.length() == 5);

    d.remove_at(3);
    CHECK(d.length() == 4);
    CHECK(d[3] == 4);
    CHECK(d[2] == 2);
    d.remove_at(1);
    CHECK(d.length() == 3);
    CHECK(d[0] == 0);
    CHECK(d[1] == 2);
}

TEST_CASE("inserts_at")
{
    Deque<int> d(10);
    int i = 0;
    while (i < 5)
    {
        d.push_back(i);
        i++;
    }

    d.insert_at(2, 23);
    CHECK(d.length() == 6);
    CHECK(d[2] == 23);
    CHECK(d[1] == 1);
    CHECK(d[3] == 2);

    d.insert_at(4, 100);
    CHECK(d.length() == 7);
    CHECK(d[4] == 100);
    CHECK(d[5] == 3);

    d.insert_at(4, 101);
    CHECK(d.length() == 8);
    CHECK(d[4] == 101);
    CHECK(d[7] == 4);

    d.insert_at(2, -2);
    CHECK(d.length() == 9);
    CHECK(d[2] == -2);
    CHECK(d[0] == 0);
    CHECK(d[8] == 4);
}

TEST_CASE("removes_at2")
{
    Deque<int> d(11);
    int i = 0;
    while (i < 7)
    {
        d.push_back(i);
        i++;
    }

    d.remove_at(1);
    CHECK(d.length() == 6);
    CHECK(d[1] == 2);
    CHECK(d[0] == 0);

    d.remove_at(4);
    CHECK(d.length() == 5);
    CHECK(d[4] == 6);
    CHECK(d[3] == 4);

    d.remove_at(2);
    CHECK(d.length() == 4);
    CHECK(d[2] == 4);
    CHECK(d[1] == 2);
}

TEST_CASE("move")
{
    Deque<int> d1(10);
    for (int i = 0; i < 8; i++)
        d1.insert_at(i, i * i);

    Deque<int> d2 = std::move(d1);

    for (int i = 0; i < d2.length(); i++)
        CHECK(d2[i] == i * i);

    CHECK(d1.capacity() == 0);
}
