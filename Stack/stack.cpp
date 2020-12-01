#ifndef _STACK_CPP
#define _STACK_CPP

#include "stack.h"
#include <stdexcept>

template <class T>
Stack<T>::Stack(): top(nullptr) {}

template <class T>
inline bool Stack<T>::empty() const
{
    return top == nullptr;
}

template <class T>
inline void Stack<T>::clear()
{
    while (!empty())
    {
        pop();
    }
    top = nullptr;
}

template <class T>
Stack<T>::Stack(const Stack<T>& rhs)
{
    Block* other_crr = rhs.top;
    Block* prev = nullptr;
    Block* crr = top;

    while (other_crr != nullptr)
    {
        crr = new Block{other_crr->data, nullptr};
        if (prev == nullptr)
            top = crr;
        else
            prev->lower = crr;
        prev = crr;
        other_crr = other_crr->lower;
    }
    
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
{
    if (this != &rhs)
    {
        clear();
        Block* other_crr = rhs.top;
        Block* prev = nullptr;
        Block* crr = top;

        while (other_crr != nullptr)
        {
            crr = new Block{other_crr->data, nullptr};
            if (prev == nullptr)
                top = crr;
            else
                prev->lower = crr;
            prev = crr;
            other_crr = other_crr->lower;
        }
    }

    return *this;
    

    
}

template <class T>
T& Stack<T>::peek()
{
    if (empty())
        throw std::out_of_range("Peeking at empty stack");
    
    return top->data;
}

template <class T>
void Stack<T>::push(const T& el)
{
    top = new Block{el, top};
}

template <class T>
bool Stack<T>::pop()
{
    if (empty())
        return false;
    
    Block* newTop = top->lower;
    delete top;
    top = newTop;
    return true;     
}

template <class T>
Stack<T>::~Stack()
{
    clear();
}

#endif