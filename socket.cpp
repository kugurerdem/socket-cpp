#include "socket.h"

using namespace std;

// Default constructor
Socket::Socket(int _domain, int _type, int _protocol){
    domain = _domain;
    type = _type;
    protocol = _protocol;
}

// opens a socket
int Socket::open(){
    socket_fd = socket(domain, type, protocol);
}

// Binds and address to a socket
int Socket::bind(string _address, int PORT){
    address.sin_family = AF_INET;   
    inet_aton(_address.c_str(), (struct in_addr *)&address.sin_addr.s_addr);
    address.sin_port = htons(PORT);

    cout << inet_ntoa((struct in_addr)address.sin_addr) << endl;

    // Attaching socket to the PORT
    int _bind = ::bind(socket_fd, (struct sockaddr *)&address, sizeof(address));
    if (_bind < 0){
        perror("Binding failed!");
    }
    return _bind;
}

// listen
int Socket::listen(int max){
    cout << "Listening on socket " << socket_fd << endl;
    return ::listen(socket_fd, max);
}

int Socket::listen(){
    return Socket::listen(MAX_QUEUE);
}

// accept
Socket Socket::accept(){
    struct sockaddr_in client_address;
    int client_address_length = sizeof(client_address);
    int clientSocket_fd = ::accept(socket_fd, (struct sockaddr *)&client_address, (socklen_t *)&client_address_length);

    if(clientSocket_fd == -1){
        cout << "Socket is not accepted" << endl;
    } else{
        cout << "Socket " << clientSocket_fd << " accepted" << endl;
    }

    // create new Socket object
    Socket clientSocket = Socket();
    clientSocket.setDescriptor(clientSocket_fd);
    clientSocket.setAddress(client_address);
    clientSocket.setAddressLength(client_address_length);

    return clientSocket;
}

// read
int Socket::read(char* buffer, int toRead){
    return ::read(socket_fd, buffer, toRead);
}

// send
int Socket::send(const void *buf, size_t len, int flags){
    return ::send(socket_fd, buf, len, flags);
}

// close
int Socket::close(){
    return ::close(socket_fd);
}
