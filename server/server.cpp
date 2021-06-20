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
    char buffer[1024] = {0};
    clientSocket.read(buffer, 1024);
    cout << buffer << endl;

    Packet packet = Packet(1633771873, 4, "abce");
    clientSocket.sendPacket(packet);

    cout << (string) packet << "- sent" << endl;
    cout << packet.getData() << "- sent" << endl;
    cout << packet.getData().c_str() << "- sent" << endl;

    return 0;
}

