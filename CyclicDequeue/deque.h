#ifndef _DEQUE
#define _DEQUE
#include <stddef.h>

template <typename T>
class Deque
{
public:
    Deque(size_t size) : buff(nullptr), cap(2 * size), len(0), head(0), tail(0)
    {
        if (!size)
            cap = 64;
        buff = new T[cap];
    }

    Deque(Deque<T> &&rhs): buff(rhs.buff), cap(rhs.cap), len(rhs.len), head(rhs.head), tail(rhs.tail)
    {
        rhs.buff = nullptr;
        rhs.cap = 0;
        rhs.len = 0;
        rhs.head = 0;
        rhs.tail = 0;
    }

    Deque<T> &operator=(Deque<T> &&rhs)
    {
        if (buff)
            delete[] buff;

        cap = rhs.cap;
        len = rhs.len;
        head = rhs.head;
        tail = rhs.tail;
        buff = rhs.buff;

        rhs.buff = nullptr;
        rhs.cap = 0;
        rhs.len = 0;
        rhs.head = 0;
        rhs.tail = 0;
        return *this;
    }

    ~Deque()
    {
        delete[] buff;
    }

    bool pop_front()
    {
        if (head == tail)
            return false;
        head = move_pos(head, 1, cap);
        len--;
        return true;
    }

    bool pop_back()
    {
        if (head == tail)
            return false;
        tail = move_pos(tail, -1, cap);
        len--;
        return true;
    }

    void push_front(const T &el)
    {
        if (len == cap)
            resize();
        head = move_pos(head, -1, cap);
        buff[head] = el;
        len++;
    }

    void push_back(const T &el)
    {
        if (len == cap)
            resize();

        buff[tail] = el;
        len++;
        tail = move_pos(tail, 1, cap);
    }

    void insert_at(size_t pos, const T &el)
    {
        if (len == cap)
            resize();
        size_t actual_pos = move_pos(pos, head, cap);

        if (actual_pos == head)
            return push_front(el);
        if (actual_pos == move_pos(tail, -1, cap))
            return push_back(el);

        size_t shift_pos;
        if (pos < len - pos)
        {
            head = move_pos(head, -1, cap);
            shift_pos = head;
            for (size_t i = 0; i < pos; i++)
            {
                buff[shift_pos] = buff[(shift_pos + 1) % cap];
                shift_pos = (shift_pos + 1) % cap;
            }
        }
        else
        {
            shift_pos = tail;
            tail = move_pos(tail, 1, cap);
            for (size_t i = 0; i < len - pos; i++)
            {
                buff[shift_pos] = buff[move_pos(shift_pos, -1, cap)];
                shift_pos = move_pos(shift_pos, -1, cap);
            }
        }
        buff[shift_pos] = el;
        len++;
    }

    void remove_at(size_t pos)
    {
        size_t actual_pos = (pos + head) % cap;
        if (actual_pos == head)
        {
            pop_front();
            return;
        }
        if (actual_pos == tail)
        {
            pop_back();
            return;
        }

        size_t shift_pos;
        if (pos < len - pos)
        {
            shift_pos = actual_pos;
            for (size_t i = 0; i < pos; i++)
            {
                buff[shift_pos] = buff[move_pos(shift_pos, -1, cap)];
                shift_pos = move_pos(shift_pos, -1, cap);
            }
            head = move_pos(head, 1, cap);
        }
        else
        {
            shift_pos = actual_pos;
            for (size_t i = 0; i < len - pos; i++)
            {
                buff[shift_pos] = buff[(shift_pos + 1) % cap];
                shift_pos = (shift_pos + 1) % cap;
            }
            tail = move_pos(tail, -1, cap);
        }
        len--;
    }

    size_t length() const
    {
        return len;
    }

    size_t capacity() const
    {
        return cap;
    }

    T &operator[](size_t pos)
    {
        return buff[(pos + head) % cap];
    }

    const T &operator[](size_t pos) const
    {
        return buff[(pos + head) % cap];
    }

private:
    // stupid c++ compilers cannot handle modulo with negative operands
    size_t move_pos(size_t pos, int offset, size_t bound)
    {
        int offset_pos = pos + offset;
        if (offset_pos < 0)
        {
            return bound + offset_pos;
        }
        return offset_pos % bound;
    }

    void resize()
    {
        T *new_buff = new T[2 * cap];
        for (size_t i = 0; i < cap; i++)
        {
            new_buff[i] = buff[(head + i) % cap];
        }
        head = 0;
        tail = cap;
        delete[] buff;
        buff = new_buff;
        cap = 2 * cap;
    }

    T *buff;
    size_t cap;
    size_t len;
    size_t head;
    size_t tail;
};

#endif