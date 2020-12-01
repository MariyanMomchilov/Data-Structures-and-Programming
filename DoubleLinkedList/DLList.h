#ifndef _DLLIST
#define _DLLIST
#include <iostream>

template <class T>
class DLList
{
private:
    struct box
    {
        T data;
        box *next, *previous;
    };

    void copy(const DLList<T> &other);
    void clear();
    box *get_node_to_right(size_t index); // --> direction
    box *get_node_to_left(size_t index);  // <-- direction

    box *first, *last;
    size_t size;

public:
    DLList();
    DLList(const T &data);
    DLList(const DLList<T> &list);
    DLList<T> &operator=(const DLList<T> &rh);
    DLList<T> operator+(const T &data) const;
    DLList<T> operator+(DLList<T> &list) const;

    DLList<T> &operator+=(const T &data);
    DLList<T> &operator+=(DLList<T> &list);

    void push_back(const T &data);
    void insertAt(const T &data, size_t index);
    void pop();
    void eraseAt(size_t index);
    size_t length() const;
    void reverse();
    bool swap(size_t i, size_t j);

    void print();

    DLList<T> createFromArray(T arr[], size_t length);

    ~DLList();

    // TO DO: add reverse iterator

    class Iterator
    {
    private:
        box *current;

    public:
        Iterator(box *crr = nullptr);
        T &operator*();
        Iterator &operator++();
        Iterator &operator--();
        bool operator!=(const Iterator &rh) const;
    };

    Iterator begin();
    Iterator preEnd();
    Iterator end();
};

#include "DLList.cpp"
#endif
