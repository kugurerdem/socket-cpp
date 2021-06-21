#include "client.h"

using namespace std;

Client::Client(){
    serverSocket = Socket();
}

int Client::run(int PORT){
    serverSocket.open(); // opens the socket
    serverSocket.setAddress("192.168.1.7", PORT); 
    serverSocket.connect();
    
    // Packet 1
    int LEN = 1600;
    char data[LEN] = {0};
    for(int i = 0; i < LEN; i++){
        data[i] = 0x61;
    }
    Packet packet = Packet(0x61616161, LEN, data);

   // Packet 2..5
    char data2[] = "merhaba";
    char data3[] = "123456789";
    char data4[] = "H1";
    char data5[] = "Hello :)";
    
    Packet packet2 = Packet(0x62616261, 7, data2);
    Packet packet3 = Packet(1, 9, data3);
    Packet packet4 = Packet(1, 2, data4);
    Packet packet5 = Packet(1, 8, data5);
    
    serverSocket.sendPacket(packet);
    serverSocket.readPacket();
    serverSocket.sendPacket(packet2);
    serverSocket.readPacket(); 
    serverSocket.sendPacket(packet3);
    serverSocket.readPacket();
    serverSocket.sendPacket(packet4);
    serverSocket.readPacket();
    serverSocket.sendPacket(packet5);
    serverSocket.readPacket(); 

    /* 
    bool condition = true;
    do
    {
        int command;
        printf("Choose a command \r\n");
        printf("0. Close the socket \r\n");
        printf("1. Send a message! \r\n");
        printf("2. Read a message! \r\n");

        cin >> command;

        if( command == 0){
            serverSocket.close();
            condition = false;
        }
        else if( command == 1){
            printf(">");
            string data = "abcd";
            cin >> data;
            Packet sendPacket = Packet(1, data.length(), data);
            serverSocket.sendPacket(sendPacket);
            cout << "Packet " << (string) sendPacket <<" sent" << endl;
        }
        else if( command == 2){
            memset(buffer, 0, 1024);
            Packet packet = serverSocket.readPacket();
            packet.log();
            // printf("Server: %s\n", buffer);
        }
    }
    while (condition); */

    return 1;
}