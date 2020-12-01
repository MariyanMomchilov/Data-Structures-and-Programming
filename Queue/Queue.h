#pragma once

template <class T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node* prev;
        Node* next;
    };

    Node* tail;
    Node* head;
public:
    Queue();
    void enqueue(const T& data);
    bool dequeue();
    bool empty() const;
    
    //head
    T& front();
    T front() const;
    
    //tail
    T& back();
    T back() const;
    ~Queue();
};


#include "Queue.cpp"