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
#include "CircularBuffer.h"

#include <pthread.h>

#define BUFFER_LENGTH 8192

typedef void * (*THREADFUNCPTR)(void *);

class Socket{

private:
    int domain, type, protocol;
    int socket_fd;
    int option;
    struct sockaddr_in address;
    int addrlen;
    CircularBuffer<char, BUFFER_LENGTH> BUFFER = CircularBuffer<char, BUFFER_LENGTH>();  // for client sockets
    // std::mutex buffer_mutex;
    pthread_t r_thread;
    pthread_mutex_t lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP; // without this, programs cannot leave locks

    int MAX_QUEUE= 10; // for server sockets
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
    int readXBytes(char* buffer, int toRead);
    int send(const void *buf, size_t len, int flags = 0);
    int close();

    int sendPacket(Packet packet);
    int readPacket(Packet& packet);

    pthread_t runReadThread();
    void* ReadThread();

    // GETTERS
    int getDescriptor(){ return socket_fd; }
    sockaddr_in getAddress(){ return address; }
    int getAddressLength(){ return addrlen; }

    // SETTERS
    int setDescriptor(int dsc){ socket_fd = dsc; }
    sockaddr_in setAddress(sockaddr_in _addr){ address = _addr; }
    int setAddressLength(int _len){ addrlen = _len; }
};