#pragma once
#include <stdexcept>
#include <iostream>

template <typename T, int N> 

class CircularBuffer{
    private:
        T buffer[N];
        int writeIndex, readIndex, max_size;
        int count;

    public:
        CircularBuffer();
        
        void enqueue(T item);
        T dequeue();
        int size();

        bool is_full();
        bool is_empty();
        
};