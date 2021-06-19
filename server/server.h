#pragma once

#include "../socket.h"
#include <string>
#include <iostream>
#include <string.h>

class Server{
private:
    Socket sv_socket;
    
public:
    Server();
    int run(int PORT);
};