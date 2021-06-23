#include "CircularBuffer.h"


template <typename T, int N> 
CircularBuffer<T,N>::CircularBuffer(){
    writeIndex = 0; 
    readIndex = 0;
    count = 0;
    max_size = N;

    T buffer[max_size];
}

template <typename T, int N> 
void CircularBuffer<T,N>::enqueue(T item){
    if( is_full() ){
        throw std::invalid_argument("Invalid insertion. The buffer is full!");
    } 

    buffer[writeIndex] = item;
    writeIndex = (writeIndex + 1) % max_size;
    count++;
}

template <typename T, int N> 
T CircularBuffer<T,N>::dequeue(){
    if( is_empty() ){
        throw std::invalid_argument("Invalid dequeue. The buffer is empty!");
    }

    T item = buffer[readIndex];
    readIndex = (readIndex + 1) % max_size;
    count--;
    return item;
}

template <typename T, int N> 
int CircularBuffer<T,N>::size(){
    return count;
    /*     
    if(writeIndex >= readIndex){
        return writeIndex - readIndex;
    } 
    return max_size - (readIndex - writeIndex); 
    */
}

template <typename T, int N> 
bool CircularBuffer<T,N>::is_full(){
    return count == max_size;
    // return readIndex == (writeIndex + 1) % max_size; 
}

template <typename T, int N> 
bool CircularBuffer<T,N>::is_empty(){
    return count == 0;
    // return readIndex == writeIndex; 
}

int main(){
    CircularBuffer<char, 4> buffer = CircularBuffer<char, 4>();
    
    char ch = 0x61;
    buffer.enqueue(ch);
    buffer.enqueue(ch);
    buffer.enqueue(ch);
    buffer.enqueue(ch);

    std::cout << buffer.dequeue() << std::endl;
    std::cout << buffer.dequeue() << std::endl;
    std::cout << buffer.dequeue() << std::endl;
    std::cout << buffer.dequeue() << std::endl;

    return 0;
}