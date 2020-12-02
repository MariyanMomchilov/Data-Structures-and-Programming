#include <iostream>
#include <stdexcept>

class Heap
{
private:
    int *array;
    size_t arraySize;
    size_t heapSize;

    inline size_t parent(size_t i) { return (i - 1)/2;}
    inline size_t left(size_t i) {return 2*i + 1;}
    inline size_t right(size_t i) {return 2*i + 2;}

    void swap(size_t i, size_t j)
    {
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    void heapify(size_t i)
    {
        if (heapSize == 0 || (left(i) >= heapSize && right(i) >= heapSize)) // is leaf
            return;
        
        int min = array[i];
        size_t swapi = i;
        if (min > array[left(i)])
        {
            swapi = left(i);
            min = array[swapi];
        }
        if (right(i) < heapSize && min > array[right(i)])
        {
            swapi = right(i);
            min = array[swapi];
        }

        if (swapi != i)
        {
            swap(i, swapi);
            heapify(swapi);
        }
    }

public:
    Heap(int *arr = nullptr, size_t size = 0): array(arr), arraySize(size), heapSize(0)
    {
        if (arraySize)
        {
            heapSize = arraySize;
            for (int i = (arraySize - 1)/2; i > -1; i--)
            {
                heapify(i);
            }
        }
    }

    inline int min() { if (heapSize) return array[0]; throw std::underflow_error("I/O to an empty heap\n");}

    void popMin()
    {
        if (heapSize == 0)
            throw std::underflow_error("Empty heap\n");

        heapSize--;
        array[0] = array[heapSize];
        heapify(0);
    }

    void decrease(size_t i, int key)
    {
        if (key < 0)
            throw std::logic_error("Cannot increase key\n");
        
        array[i] -= key;
        
        while (i > 0 && array[i] < array[parent(i)])
        {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    void insert(int key)
    {
        if (heapSize < arraySize)
        {
            array[heapSize] = key;
            int i = heapSize++;
            while (i > 0 && array[i] < array[parent(i)])
            {
                swap(i, parent(i));
                i = parent(i);
            }
            return;       
        }
        throw std::overflow_error("Heap overflow\n");
    }


    ~Heap() = default;
};




int main()
{
    int arr[] = {3, 10, 1, 7, 8, 0};
    Heap min(arr, 6);
    min.popMin();
    min.decrease(0, 10);
    min.decrease(3, 20);
    min.insert(-6);
    min.popMin();
    min.popMin();
    min.popMin();
    min.popMin();
    min.popMin();
    min.popMin();
    min.insert(100);
    min.insert(0);
    return 0;
}