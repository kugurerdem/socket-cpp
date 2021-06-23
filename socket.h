#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string>
#include <string.h>
#include <iostream>
#include "packet.h"
#include "utils.h"

class Socket{

private:
    int domain, type, protocol;
    int socket_fd;
    struct sockaddr_in address;
    int addrlen;
    int BUFFER_LENGHT = 8192;
    char buffer[BUFFER_LENGTH];

    int MAX_QUEUE= 10;
public:
    Socket(int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);
    int open();
    int setAddress( std::string address, int PORT);
    int bind(std::string address, int PORT);
    int listen();
    int listen(int max);
    int connect();
    Socket accept();
    int read(char* buffer, int toRead);
    int send(const void *buf, size_t len, int flags = 0);
    int close();

    int sendPacket(Packet packet);
    int readPacket(Packet& packet);

    // GETTERS
    int getDescriptor(){ return socket_fd; }
    sockaddr_in getAddress(){ return address; }
    int getAddressLength(){ return addrlen; }

    // SETTERS
    int setDescriptor(int dsc){ socket_fd = dsc; }
    sockaddr_in setAddress(sockaddr_in _addr){ address = _addr; }
    int setAddressLength(int _len){ addrlen = _len; }
};