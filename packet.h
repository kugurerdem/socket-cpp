#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "utils.h"

// 4 bytes for type
// 4 bytes for size
// size-many bytes for data
class Packet{
private:
    uint32_t type; // Type of the Packet, hexadecimal
    uint32_t size; // Size of the data, hexadecimal
    std::string data; // Data
public:
    Packet(uint32_t _type, uint32_t _size, std::string _data);
    Packet(char* buffer);

    operator std::string();

    // SETTERS
    void setType(uint32_t _type){ type = _type;}
    void setSize(uint32_t _size){ size = _size;}
    void setData(std::string _data){ data = _data;}

    // GETTERS
    uint32_t getType(){ return type;}
    uint32_t getSize(){ return size;}
    std::string getData(){ return data;}
};