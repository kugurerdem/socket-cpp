#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "utils.h"

using namespace std;

// 4 bytes for type
// 4 bytes for size
// size-many bytes for data
class Packet{
private:
    uint32_t type; // Type of the Packet, hexadecimal
    uint32_t size; // Size of the data, hexadecimal
    char* data; // Data
public:
    Packet();
    Packet(uint32_t _type, uint32_t _size, char* _data);

    operator char*();
    void log();

    // SETTERS
    void setType(uint32_t _type){ type = _type;}
    void setSize(uint32_t _size){ size = _size;}
    void setData(char* _data){ data = _data;}
    
    // GETTERS
    uint32_t getType(){ return type;}
    uint32_t getSize(){ return size;}
    char* getData(){ return data;}
};