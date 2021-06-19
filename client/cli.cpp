// Client side C/C++ program to demonstrate Socket programming
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

using namespace std;

int main(int argc, char const *argv[])
{
    setbuf(stdout, NULL);

    int sock = 0, valread;
    struct sockaddr_in serverAddress;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_aton("192.168.1.7", &serverAddress.sin_addr); // enter ip address here

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "192.168.1.7", &serverAddress.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    bool condition = true;
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
            close(sock);
            condition = false;
            break;
        case 1:
            printf(">");
            char message[1024];
            cin >> message;
            send(sock, message, strlen(message), 0);
            printf("\"%s\" \n  ", message);
            break;
        case 2:
            memset(buffer, 0, 1024);
            read(sock, buffer, 1024);
            printf("Server: %s\n", buffer);
            break;
        }
    }
    while (condition);

    return 0;
}