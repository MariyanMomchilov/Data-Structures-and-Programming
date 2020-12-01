#pragma once

#include "Queue.h"

template<class T>
Queue<T>::Queue(): tail(nullptr), head(nullptr){}

template<class T>
void Queue<T>::enqueue(const T& data)
{
    if (empty())
    {
        tail = head = new Node{data, nullptr, nullptr};
    }
    else
    {
        Node* new_tail = new Node{data, nullptr, tail};
        tail->prev = new_tail;
        tail = new_tail;

        if (head->prev == nullptr)
            head->prev = tail;
    }
    
}

template<class T>
bool Queue<T>::dequeue()
{
    if (head == nullptr)
        return false;
    
    Node* tmp = head;
    head = tmp->prev;
    delete tmp;
    if (head == nullptr)
        tail = nullptr;
    return true;
}

template<class T>
inline bool Queue<T>::empty() const
{
    return head == nullptr;
}

//head
template<class T>
T& Queue<T>::front()
{
    return head->data;
}

template<class T>
T Queue<T>::front() const
{
    return head->data;
}


//tail
template<class T>
T& Queue<T>::back()
{
    return tail->data;
}

template<class T>
T Queue<T>::back() const
{
    return tail->data;
}

template<class T>
Queue<T>::~Queue()
{
    Node* erase;
    while (!empty())
    {
        erase = head;
        head = head->prev; 
        delete erase;
    }
}