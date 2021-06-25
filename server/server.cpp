#include "server.h"
using namespace std;



Server::Server(){
    sv_socket = Socket();
}

int Server::run(int PORT){
    sv_socket.open();
    sv_socket.bind("0.0.0.0", PORT);
    sv_socket.listen(10);

    // accept a new client
    Socket clientSocket = sv_socket.accept();
    bool condition = true;

    pthread_t r_thread = clientSocket.runReadThread();
    
    cout << "hi" << endl;
    Packet packet;
    
    while(true){
        clientSocket.readPacket(packet);
    }
    
    
    pthread_join(r_thread, NULL);

    return 0;
}

