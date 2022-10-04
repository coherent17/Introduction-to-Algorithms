#ifndef HEAPSORT_H
#define HEAPSORT_H

//index in the heap array start from 1
#define PARENT(i) i / 2
#define LEFT(i) 2 * i
#define RIGHT(i) 2 * i + 1

class Heap{
    private:
        int *A;
        int heap_size;

    public:
        //constructor
        Heap(int *A, int heap_size);

        //method
        void Max_Heapify(int i);
        void Build_Max_Heap();
        void HeapSort();
};

#endif