#pragma once

#include "../socket.h"
#include "../packet.h"
#include <string>
#include <iostream>
#include <string.h>

class Server{
private:
    Socket sv_socket;
    
public:
    Server();
    int run(int PORT);
    void* ClientThread(Socket socket);
};