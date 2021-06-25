#include "server.h"
using namespace std;

struct thread_args{
    Server* instance;
    Socket socket;
};

void* thread_helper(void *voidArgs) {
    thread_args *args = (thread_args*)voidArgs;
    args->instance->ClientThread(args->socket);
}

Server::Server(){
    sv_socket = Socket();
}

int Server::run(int PORT){
    sv_socket.open();
    sv_socket.bind("0.0.0.0", PORT);
    int MAX_QUEUE = 10;

    sv_socket.listen(MAX_QUEUE);

    Socket sockets[MAX_QUEUE];
    pthread_t threads[MAX_QUEUE];

    // Accept new clients
    int index = 0;
    while(true){
        sockets[index] = sv_socket.accept();
        
        // define arguments for the thread_helper
        thread_args args;
        args.instance = this;
        args.socket = sockets[index];

        pthread_create(&threads[index], NULL, (THREADFUNCPTR) &thread_helper, &args);
        index++;
    }

    // Join client threads
    for(int i = 0; i < MAX_QUEUE; i++){
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}

void* Server::ClientThread(Socket socket){
    pthread_t r_thread = socket.runReadThread();
    
    Packet packet;
    while(true){
        socket.readPacket(packet);
        cout << "-- From socket: " << socket.getDescriptor() << endl;
        packet.log();
    }
    
    pthread_join(r_thread, NULL);
}
