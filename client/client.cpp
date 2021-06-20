#include "client.h"

using namespace std;

Client::Client(){
    serverSocket = Socket();
}

int Client::run(int PORT){
    serverSocket.open(); // opens the socket
    serverSocket.setAddress("192.168.1.7", PORT); 
    serverSocket.connect();
    
    bool condition = true;
    char buffer[1024] = {0};
    do
    {
        int command;
        printf("Choose a command \r\n");
        printf("0. Close the socket \r\n");
        printf("1. Send a message! \r\n");
        printf("2. Read a message! \r\n");

        cin >> command;

        switch (command)
        {
        case 0:
            serverSocket.close();
            condition = false;
            break;
        case 1:
            printf(">");
            char message[1024];
            cin >> message;
            serverSocket.send(message, strlen(message), 0);
            printf("\"%s\" \n  ", message);
            break;
        case 2:
            memset(buffer, 0, 1024);
            Packet packet = serverSocket.readPacket();
            cout << packet.getType() << endl;
            cout << packet.getSize() << endl;
            cout << packet.getData().c_str() << endl;
            // printf("Server: %s\n", buffer);
            break;
        }
    }
    while (condition);

    return 1;
}