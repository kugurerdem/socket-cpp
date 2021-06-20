#pragma once

#include "../socket.h"
#include "../packet.h"
#include <string>
#include <iostream>

class Client{
    private:
        Socket serverSocket;
    public:
        Client();
        int run(int PORT=8080);
};