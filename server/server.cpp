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
    for(int i = 0; i < 5; i++){
        // read a packet
        Packet packet = clientSocket.readPacket();
        // packet.log();

        // send the packet back
        packet.setType(2);
        clientSocket.sendPacket(packet);

        // packet.log();
    }

    return 0;
}

