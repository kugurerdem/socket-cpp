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
    printf("%s \r\n", buffer);
    cout << buffer << endl;

    clientSocket.send(buffer, strlen(buffer), 0);
    printf("%s - message sent \r\n", buffer);

    return 0;
}

