#include "CircularBuffer.h"


template <typename T, int N> 
CircularBuffer<T,N>::CircularBuffer(){
    writeIndex = 0; 
    readIndex = 0;
    count = 0;
    max_size = N;

    T buffer[max_size] = {0};
}

template <typename T, int N> 
void CircularBuffer<T,N>::enqueue(T item){
    if( is_full() ){
        throw std::runtime_error("Invalid insertion. The buffer is full!");
    } 

    buffer[writeIndex] = item;
    writeIndex = (writeIndex + 1) % max_size;
    count++;
}

template <typename T, int N> 
void CircularBuffer<T,N>::enqueue(T* items, int LEN){
    // std::cout << "enqueue called" << std::endl;
    if( LEN <= max_size - count){
        // std::cout << "inside the enqueue" << std::endl;
        for(int i = 0; i < LEN; i++){
            enqueue( items[i]); 
            // std::cout << i << " : " << buffer[i] << std::endl;
        }
    }
}


template <typename T, int N> 
T CircularBuffer<T,N>::dequeue(){
    if( is_empty() ){
        throw std::runtime_error("Invalid dequeue. The buffer is empty!");
    }

    T item = buffer[readIndex];
    readIndex = (readIndex + 1) % max_size;
    count--;
    return item;
}

template <typename T, int N> 
int CircularBuffer<T,N>::dequeue(T* items, int LEN){
    // std::cout << "dequeue called" << std::endl; 
    if(LEN <= count){
        // std::cout << "inside of the dequeue" << std::endl;
        for(int i = 0; i < LEN; i++){
            T item = dequeue();
            // std::cout << i << " : " << item << std::endl;
            items[i] = item;
        }
    }  

    return -1;
}

template <typename T, int N> 
int CircularBuffer<T,N>::size(){
    return count;
}

template <typename T, int N> 
bool CircularBuffer<T,N>::is_full(){
    return count == max_size;
}

template <typename T, int N> 
bool CircularBuffer<T,N>::is_empty(){
    return count == 0;
}

/* int main(){
    CircularBuffer<char, 3> buffer = CircularBuffer<char, 3>();
    
    char chars[] = "asd";

    buffer.enqueue(chars, 3);

    char m[3];
    buffer.dequeue(m, 3);

    std::cout << m << std::endl;
    std::cout << m[0] << std::endl; 

    return 0;
} */