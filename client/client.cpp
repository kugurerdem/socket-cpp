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
    
    while(true){
        serverSocket.sendPacket(packet);
/*         serverSocket.sendPacket(packet2); 
        serverSocket.sendPacket(packet3);
        serverSocket.sendPacket(packet4);
        serverSocket.sendPacket(packet5);  */
        sleep(1);
    }

    

    return 1;
}