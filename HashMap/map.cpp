#ifndef __MAPCPP
#define __MAPCPP
#include <stdexcept>
#include "map.h"


template <class Key, class Value>
Map<Key, Value>::Map(const std::function<size_t(const Key&)> &h, size_t s) : size(s), table(nullptr), hash(h)
{
    table = new Entity*[size];

    for (int i = 0; i < size; i++)
        table[i] = nullptr;    
}

template <class Key, class Value>
size_t Map<Key, Value>::applyHash(const Key& key) const
{
    return hash(key) % size;
}

template <class Key, class Value>
bool Map<Key, Value>::hasKey(const Key& key) const 
{
    size_t index = applyHash(key);
    return table[index] != nullptr && table[index]->key == key;
}

template <class Key, class Value>
typename Map<Key, Value>::Entity* Map<Key, Value>::getEntity(const Key& key)
{
    size_t index = applyHash(key);
    if (table[index] == nullptr)
        table[index] = new Entity{key, Value(), nullptr};
    else
    {    
        Entity *crr = table[index];
        while (crr != nullptr && crr->key != key)
        {
            crr = crr->next;
        }
        if (crr == nullptr)
            table[index] = new Entity{key, Value(), table[index]};
        else
            return crr;
    }
    return table[index];
}


template <class Key, class Value>
Value Map<Key, Value>::operator[](const Key& key) const 
{
    return getEntity(key)->value;
}

template <class Key, class Value>
Value& Map<Key, Value>::operator[](const Key& key) 
{
    return getEntity(key)->value;
}

template <class Key, class Value>
Map<Key, Value>::ConstIterator::ConstIterator(): table(nullptr),size(0), index(0), current(nullptr) {}



template <class Key, class Value>
void Map<Key, Value>::ConstIterator::setCurrentUsingIndex()
{
    while (index < size && table[index] == nullptr)
    {
        index++;
    }
    if (index < size)
        current = table[index];

}

template <class Key, class Value>
Map<Key, Value>::ConstIterator::ConstIterator(Entity **t, size_t s): table(t), size(s), index(0), current(nullptr)
{
    setCurrentUsingIndex();
}

template <class Key, class Value>
typename Map<Key, Value>::ConstIterator & Map<Key, Value>::ConstIterator::operator++()
{
    if (current == nullptr)
        throw std::range_error("Using ++ on end ConstIterator\n");
    if (current->next != nullptr)
        current = current->next;
    else
    {
        index++;
        current = nullptr;
        setCurrentUsingIndex();
    }
    return *this;
}

template <class Key, class Value>
Key Map<Key, Value>::ConstIterator::operator*() const
{
    if (current == nullptr)
        throw std::logic_error("Using operator*() on end ConstIterator\n");
    return current->key;

}

template <class Key, class Value>
bool Map<Key, Value>::ConstIterator::operator!=(const ConstIterator& it) const
{
    return current != it.current;
}

template <class Key, class Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::begin()
{
    return ConstIterator(table, size);
}

template <class Key, class Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::end()
{
    return ConstIterator();
}


template <class Key, class Value>
Map<Key, Value>::~Map()
{
    for (int i = 0; i < size; i++)
    {
        if (table[i] != nullptr)
        {
            Entity *tmp = nullptr;
            Entity *crr = table[i];
            while (crr != nullptr)
            {
                tmp = crr;
                crr = crr->next;
                delete tmp;
            }
        }
    }
    if (size != 0)
        delete[] table;
}

#endif