#ifndef __MAP
#define __MAP
#include <iostream>
#include <functional>

template <class Key, class Value>
class Map
{
private:
    
    struct Entity
    {
        Key key;
        Value value;
        Entity *next;
    };

    size_t size;
    Entity **table;
    std::function<size_t(const Key&)> hash;
    size_t applyHash(const Key&) const;
    Entity* getEntity(const Key&);

public:
    Map(const std::function<size_t(const Key&)> &h, size_t s = 0);
    bool hasKey(const Key&) const;
    Value operator[](const Key&) const;
    Value& operator[](const Key&);

    class ConstIterator
    {
    private:
        Entity **table;
        size_t size;
        size_t index;
        Entity *current;

        void setCurrentUsingIndex();

    public:
        ConstIterator();
        ConstIterator(Entity **, size_t);

        ConstIterator& operator++(); 
        Key operator*() const;
        bool operator!=(const ConstIterator&) const;
    };

    ConstIterator begin();
    ConstIterator end();
    
    ~Map();
    
};

#include "map.cpp"

#endif