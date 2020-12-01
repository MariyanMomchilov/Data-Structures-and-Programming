#ifndef _DLLIST_CPP
#define _DLLIST_CPP
#include "DLList.h"
#include <iostream>
#include <exception>

template <class T>
DLList<T>::DLList() : first(nullptr), last(nullptr), size(0) {}

template <class T>
DLList<T>::DLList(const T &data) : first(new box{data, nullptr, nullptr}, last(nullptr)), size(1)
{
    last = first;
}

template <class T>
void DLList<T>::copy(const DLList<T> &other)
{

    size = other.size;

    if (other.first != nullptr)
    {

        // YIKES
        box *l_other_crr = other.first;
        box *l_crr = nullptr, *l_prev = nullptr;
        box *r_other_crr = other.last;
        box *r_crr = nullptr, *r_next = nullptr;
        size_t mid = size / 2;

        // YIKES
        while (mid != 0)
        {
            // left part
            l_crr = new box{l_other_crr->data, nullptr, l_prev};
            if (l_crr->previous == nullptr)
                first = l_crr;
            if (l_prev != nullptr)
                l_prev->next = l_crr;
            l_prev = l_crr;
            l_other_crr = l_other_crr->next;

            // right part
            r_crr = new box{r_other_crr->data, r_next, nullptr};
            if (r_crr->next == nullptr)
                last = r_crr;
            if (r_next != nullptr)
                r_next->previous = r_crr;
            r_next = r_crr;
            r_other_crr = r_other_crr->previous;

            mid--;
        }
        if (size % 2)
        {
            l_crr = new box{l_other_crr->data, r_crr, l_crr};
            l_crr->previous->next = l_crr;
        }
        else
            l_crr->next = r_crr;
        r_crr->previous = l_crr;
    }
}

template <class T>
DLList<T> &DLList<T>::operator=(const DLList<T> &rh)
{
    if (this != &rh)
    {
        clear();
        copy(rh);
    }
    return *this;
}

template <class T>
void DLList<T>::clear()
{
    if (first != nullptr)
    {
        box *crr = first;
        box *tmp;
        while (crr != nullptr)
        {
            tmp = crr;
            crr = crr->next;
            delete tmp;
        }
    }
}

template <class T>
DLList<T>::DLList(const DLList<T> &list) : first(nullptr), last(nullptr), size(0)
{
    copy(list);
}

template <class T>
DLList<T> DLList<T>::operator+(const T &data) const
{
    DLList<T> result = *this;
    if (result.first == nullptr)
    {
        result.first = result.last = new box{data, nullptr, nullptr};
    }
    else
    {
        result.first = new box{data, result.first, nullptr};
        result.first->next->previous = result.first;
    }
    result.size++;
    return result;
}

//Concatenates 2 lists and returns a new one, not the as the operator + above!!
template <class T>
DLList<T> DLList<T>::operator+(DLList<T> &list) const
{
    DLList<T> list1Cpy = *this;
    list1Cpy += list;

    return list1Cpy;
}

// adds element in front of the list
template <class T>
DLList<T> &DLList<T>::operator+=(const T &data)
{
    if (first == nullptr)
    {
        first = last = new box{data, nullptr, nullptr};
    }
    else
    {
        first = new box{data, first, nullptr};
        first->next->previous = first;
    }
    size++;
    return *this;
}

//Appends to this list, not the same the above += !!
template <class T>
DLList<T> &DLList<T>::operator+=(DLList<T> &list)
{
    DLList<T> copyOfList = list;
    size += list.size;

    if (first != nullptr)
    {
        last->next = copyOfList.first;
        last->next->previous = last;
        copyOfList.first = nullptr;
    }
    else
    {
        first = copyOfList.first;
        copyOfList.first = nullptr;
    }
    last = copyOfList.last;
    return *this;
}

template <class T>
void DLList<T>::push_back(const T &data)
{
    if (last == nullptr)
        first = last = new box{data, nullptr, nullptr};
    else
    {
        last = new box{data, nullptr, last};
        last->previous->next = last;
    }
    size++;
}

template <class T>
void DLList<T>::pop()
{
    if (last != nullptr)
    {
        box *tmp = last;
        last = last->previous;
        last->next = nullptr;
        delete tmp;
        if (last == first)
            first = last = nullptr;
        size--;
        return;
    }
    throw std::out_of_range("Read/Write on null pointer");
}

// -->
template <class T>
typename DLList<T>::box *DLList<T>::get_node_to_right(size_t index)
{
    box *crr = first;

    if (first != nullptr)
    {
        while (index != 0)
        {
            index--;
            crr = crr->next;
        }
    }
    return crr;
}

// <--
template <class T>
typename DLList<T>::box *DLList<T>::get_node_to_left(size_t index)
{
    box *crr = last;

    if (last != nullptr)
    {
        while (size - 1 != index)
        {
            index++;
            crr = crr->previous;
        }
    }
    return crr;
}

template <class T>
void DLList<T>::eraseAt(size_t index)
{
    if (first != nullptr && index < size)
    {

        box *node;
        size_t mid = size / 2;
        if (index <= mid)
            node = get_node_to_right(index);
        else
            node = get_node_to_left(index);

        if (node != nullptr)
        {
            box *tmp = node->next;
            if (tmp != nullptr)
            {
                node->next = tmp->next;
                if (node->next != nullptr)
                    node->next->previous = node;
                else
                    last = node;
                delete tmp;
                size--;
                return;
            }
        }
    }
    throw std::out_of_range("Read/Write on null pointer");
}

template <class T>
void DLList<T>::insertAt(const T &data, size_t index)
{
    if (first == nullptr)
    {
        push_back(data);
        size++;
        return;
    }

    size_t mid = size / 2 - 1;
    box *node;
    if (index <= mid)
        node = get_node_to_right(index);
    else
        node = get_node_to_left(index);

    if (node != nullptr)
    {
        node->next = new box{data, node->next, node};
        if (node == last)
            last = node->next;
        size++;
    }
    if (node->next->next != nullptr)
        node->next->next->previous = node->next;
}

template <class T>
DLList<T>::~DLList()
{
    clear();
}

template <class T>
void DLList<T>::print()
{
    for (T &x : *this)
    {
        std::cout << x << " <-> ";
    }
    std::cout << "nullptr \n";
}

template <class T>
size_t DLList<T>::length() const
{
    return size;
}

template <class T>
void DLList<T>::reverse()
{
    box *tmp;
    box *crr = first;
    while (crr != nullptr)
    {
        tmp = crr->previous;
        crr->previous = crr->next;
        crr->next = tmp;
        if (tmp == nullptr)
        {
            last = crr;
        }
        first = crr;
        crr = crr->previous;
    }
}

template <class T>
bool DLList<T>::swap(size_t i, size_t j)
{
    size_t mid = size / 2 - 1;

    box *i_th = i <= mid ? get_node_to_right(i) : get_node_to_left(i);
    box *j_th = i <= mid ? get_node_to_right(j) : get_node_to_left(j);
    bool predicate = i_th == nullptr || j_th == nullptr;
    if (!predicate)
    {
        T tmp_data = i_th->data;

        i_th->data = j_th->data;

        j_th->data = tmp_data;
    }
    return !predicate;
}

template <class T>
DLList<T> DLList<T>::createFromArray(T arr[], size_t length)
{
    DLList<T> list;
    list.size = length;
    box *prev = nullptr;
    box *current = list.first;
    for (int i = 0; i < length; i++)
    {
        current = new box{arr[i], nullptr, prev};
        if (prev != nullptr)
            prev->next = current;
        if (i == 0)
            list.first = current;
        prev = current;
    }
    list.last = current;
    return list;
}

template <class T>
DLList<T>::Iterator::Iterator(box *crr) : current(crr)
{
}

template <class T>
T &DLList<T>::Iterator::operator*()
{
    if (current == nullptr)
        throw std::out_of_range("Read/Write on null pointer");
    return current->data;
}

template <class T>
typename DLList<T>::Iterator &DLList<T>::Iterator::operator++()
{
    if (current == nullptr)
        throw std::out_of_range("Read/Write on null pointer");

    current = current->next;
    return *this;
}

template <class T>
typename DLList<T>::Iterator &DLList<T>::Iterator::operator--()
{
    if (current == nullptr)
        throw std::out_of_range("Read/Write on null pointer");

    current = current->previous;
    return *this;
}

template <class T>
bool DLList<T>::Iterator::operator!=(const Iterator &rh) const
{
    return current != rh.current;
}

template <class T>
typename DLList<T>::Iterator DLList<T>::begin()
{
    return Iterator(first);
}

template <class T>
typename DLList<T>::Iterator DLList<T>::preEnd()
{
    return Iterator(last);
}

template <class T>
typename DLList<T>::Iterator DLList<T>::end()
{
    return Iterator();
}

#endif