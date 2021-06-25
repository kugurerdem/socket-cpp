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
    for(int i = 0; i < LEN; i++){ data[i] = 0x61; }

    // Packet 2..5
    char data2[] = "merhaba\0";
    char data3[] = "123456789\0";
    char data4[] = "H1\0";
    char data5[] = "Hello :)\0";

    int PACKETS_LEN = 5;
    Packet packets[PACKETS_LEN];
    packets[0] = Packet(0x60606060, LEN, data);
    packets[1] = Packet(2, strlen(data2), data2);
    packets[2] = Packet(3, strlen(data3), data3);
    packets[3] = Packet(4, strlen(data4), data4);
    packets[4] = Packet(5, strlen(data5), data5);
    
    srand((unsigned) time(0));
    while(true){
        int index = rand() % PACKETS_LEN;
        serverSocket.sendPacket(packets[index]);

        sleep(0.01);
    }

    return 1;
}