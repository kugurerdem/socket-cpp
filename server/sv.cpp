#define _BSD_SOURCE
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8080

using namespace std;

//deneme
void error(char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
    setbuf(stdout, NULL);
    int serverSocket, clientSocket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    int MAX_QUEUE = 10;

    // Creating socket file descriptor
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == 0)
    {
        error("Socket failed!");
    }

    address.sin_family = AF_INET;
    inet_aton("0.0.0.0", (struct in_addr *)&address.sin_addr.s_addr);
    address.sin_port = htons(PORT);

    cout << inet_ntoa((struct in_addr)address.sin_addr) << endl;

    // Attaching socket to the PORT
    if (bind(serverSocket, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        error("Binding failed!");
    }

    // Listening...
    if (listen(serverSocket, MAX_QUEUE) < 0)
    {
        error("listen");
    }


    clientSocket = accept(serverSocket, (struct sockaddr *)&address,
                            (socklen_t *)&addrlen);
    if (clientSocket < 0)
    {
        error("accept");
    }

    while( true){
        read(clientSocket, buffer, 2);
        printf("%s\n", buffer);
        read(clientSocket, buffer, 1);
        printf("%s\n", buffer);
        read(clientSocket, buffer, 1);
        printf("%s\n", buffer);
        send(clientSocket, buffer, strlen(buffer), 0);
        printf("%s - message sent\n", buffer);
        memset(buffer, 0, 1024);
    }

    return 0;
}