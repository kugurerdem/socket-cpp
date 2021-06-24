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
    CircularBuffer(){
        writeIndex = 0; 
        readIndex = 0;
        count = 0;
        max_size = N;

        T buffer[max_size] = {0};
    }

    void enqueue(T item){
        if( is_full() ){
            throw std::runtime_error("Invalid insertion. The buffer is full!");
        } 

        buffer[writeIndex] = item;
        writeIndex = (writeIndex + 1) % max_size;
        count++;
    }

    void enqueue(T* items, int LEN){
        // std::cout << "enqueue called" << std::endl;
        if( LEN <= max_size - count){
            // std::cout << "inside the enqueue" << std::endl;
            for(int i = 0; i < LEN; i++){
                enqueue( items[i]); 
                // std::cout << i << " : " << buffer[i] << std::endl;
            }
        }
    }


    T dequeue(){
        if( is_empty() ){
            throw std::runtime_error("Invalid dequeue. The buffer is empty!");
        }

        T item = buffer[readIndex];
        readIndex = (readIndex + 1) % max_size;
        count--;
        return item;
    }

    int dequeue(T* items, int LEN){
        // std::cout << "dequeue called" << std::endl; 
        if(LEN <= count){
            // std::cout << "inside of the dequeue" << std::endl;
            for(int i = 0; i < LEN; i++){
                T item = dequeue();
                // std::cout << i << " : " << item << std::endl;
                items[i] = item;
            }

            return LEN;
        }  

        return -1;
    }

    int size(){
        return count;
    }

    bool is_full(){
        return count == max_size;
    }

    bool is_empty(){
        return count == 0;
    }
};