#include "packet.h"
#include "utils.h"

Packet::Packet(uint32_t _type, uint32_t _size, std::string _data){
    type = _type;
    size = _size;
    data = _data;
}

// TO-DO
Packet::Packet(char* buffer){
    
}

Packet::operator std::string(){
    std::string packet; 
            
    packet += uint32_to_string(type);
    packet += uint32_to_string(size);
    for(int i = 0; i < size; i++){
        packet += data[i];
    }

    return packet;
}
