#include "packet.h"
#include "utils.h"

using namespace std;

/* Packet::Packet(uint32_t _type, uint32_t _size, std::string _data){
    type = _type;
    size = _size;

    data = (char*) _data.c_str();
}

Packet::Packet(uint32_t _type, std::string _data){
    Packet(_type, _data.length(), _data);
} */

Packet::Packet(uint32_t _type, uint32_t _size, char* _data){
    type = _type;
    size = _size;
    data = _data;
}

/* Packet::operator std::string(){
    std::string packet; 
            
    packet += uint32_to_string(type);
    packet += uint32_to_string(size);
    for(int i = 0; i < size; i++){
        packet += data[i];
    }

    return packet;
}
 */
Packet::operator char*(){
    char* packet = new char[size+8];
    uint32_to_chars(type, packet);
    uint32_to_chars(size, (packet+4));
    for(int i = 0; i < size; i++){
        packet[i+8] = (char) data[i];
    }
    /*      
    cout << "Packet (char*):";
    for(int i = 0; i < size + 8; i++){
        cout << packet[i];
    }
    cout << std::endl; 
    */

    return packet;
} 

void Packet::log(){
    cout << "Packet Log" << std::endl;
    cout << "TYPE:" << getType() << ", ";
    cout << "DATA SIZE:" << getSize() << ", ";
    
    cout << "DATA:";
    for(int i = 0; i < getSize(); i++){
        cout << data[i];
    }
    cout << endl;
}