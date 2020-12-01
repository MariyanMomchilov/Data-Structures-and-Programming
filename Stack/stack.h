#ifndef _STACK
#define _STACK

template <typename T>
class Stack
{
private:
    struct Block
    {
        T data;
        Block* lower;
    };

    Block* top;
    void clear();

public:
    Stack();
    Stack(const Stack<T>& rhs);
    Stack& operator=(const Stack<T>& rhs);
    T& peek();
    void push(const T& el);
    bool pop();
    bool empty() const;
    ~Stack();
};

#include "stack.cpp"

#endif