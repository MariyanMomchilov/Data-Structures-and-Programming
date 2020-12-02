#include <iostream>
#include <stdexcept>

class Heap
{
private:
    int* array;
    size_t arraySize;
    size_t heapSize;


    inline size_t parent(size_t i) { return (i - 1)/2;}
    inline size_t left(size_t i) {return 2*i + 1;}
    inline size_t right(size_t i) {return 2*i + 2;}

    void heapify(size_t i)
    {
        if (i >= heapSize) return;

        int max = array[i];
        int li = left(i);
        int ri = right(i);
        if (li < arraySize && max < array[li])
            max = array[li];
        if (ri < arraySize && max < array[ri])
            max = array[ri];

        if (max == array[ri])
        {
            array[ri] = array[i];
            array[i] = max;
            heapify(ri);
        }
        else if (max == array[li])
        {
            array[li] = array[i];
            array[i] = max;
            heapify(li);
        }
    }

public:
    Heap(int *arr = nullptr, size_t arrayS = 0): array(arr), arraySize(arrayS), heapSize(0)
    {
        if (arraySize != 0)
        {
            heapSize = arraySize/2 + 1;
            for (int i = arraySize/2 - 1; i > -1; i--)
            {
                heapify(i);
                heapSize++;
            }
        }
    }

    inline int max()
    {
        if (heapSize > 0)
            return array[0];

        throw std::underflow_error("I/O to an empty heap\n");
    }

    int popMax()
    {
        if (heapSize > 0)
        {
            int max = array[0];
            --heapSize;
            if (heapSize > 0)
            {
                array[0] = array[heapSize];
                heapify(0);
            }
            return max;
        }

        throw std::underflow_error("I/O to an empty heap\n");

    }

    void increaseKey(size_t i, int incr)
    {
        if (incr < 0)
            throw std::logic_error("Decreasing key value\n");
        
        array[i] += incr;
        int crr = i;
        int crrp = parent(crr);
        int tmp;

        while (crrp >= 0 && array[crrp] < array[crr])
        {
            tmp = array[crr];
            array[crr] = array[crrp];
            array[crrp] = tmp;

            crr = crrp;
            crrp = parent(crrp);    
        }
    }

    void insert(int key)
    {
        if (heapSize == arraySize)
            throw std::overflow_error("Inserting in a full heap\n");
        
        heapSize++;
        int i = heapSize-1;
        array[i] = key;
        int tmp;

        while (i > 0 && array[i] > array[parent(i)])
        {
            //!
            tmp = array[i];
            array[i] = array[parent(i)];
            i = parent(i);
            array[i] = tmp;
        }
        
    }

    ~Heap() = default;

};


int main()
{
    //int arr[6] = {4, 14, 7, 2, 1, 8};
    int arr[7] = {10, 5, 15, 3, 4, 8, 9};
    Heap max(arr, 7);
    max.increaseKey(5, 10);
    max.popMax();
    max.insert(30);

}