#pragma once

#include "../socket.h"
#include "../packet.h"
#include <string>
#include <iostream>
#include <string.h>

class Server{
private:
    Socket sv_socket;
    int MAX_QUEUE;
    // pthread_mutex_t log_lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
public:
    Server();
    int run(int PORT);
    void* ClientThread(Socket socket);
};