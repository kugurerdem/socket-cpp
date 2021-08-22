#include "socket.h"

// Default constructor
Socket::Socket(int _domain, int _type, int _protocol){
    domain = _domain;
    type = _type;
    protocol = _protocol;
    option = 1;
}

// opens a socket
int Socket::open(){
    socket_fd = socket(domain, type, protocol);
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
}

// sets the address of the socket
int Socket::setAddress(string _address, int PORT){
    address.sin_family = AF_INET;   
    inet_aton(_address.c_str(), (struct in_addr *)&address.sin_addr.s_addr);
    address.sin_port = htons(PORT);

    cout << inet_ntoa((struct in_addr)address.sin_addr) << endl;
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, _address.c_str(), &address.sin_addr) <= 0)
    {
        cout << "\nInvalid address/ Address not supported \n" << endl;
        return -1;
    }

    return 1;
}   

// Binds and address to a socket
int Socket::bind(string _address, int PORT){
    setAddress(_address, PORT);
    
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

// connect
int Socket::connect(){
    int _connect = ::connect(socket_fd,(struct sockaddr *)&address, sizeof(address) );
    if (_connect < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    return 1;
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

// read from circular buffer
int Socket::read(char* buffer, int toRead){
    int buffer_size = BUFFER.size();
    // cout << "buffer_size: " << buffer_size << endl;
    // cout << "input toRead: " << toRead << endl;
    if( buffer_size < toRead){ 
        toRead = buffer_size; 
    }
    // cout << "updated toRead: " << toRead << endl;

    pthread_mutex_lock(&lock);
    BUFFER.dequeue(buffer, toRead);
    pthread_mutex_unlock(&lock);

    return toRead;
}

// reads exactly toRead bytes
int Socket::readXBytes(char* buffer, int toRead){
    int i = 0;
    int totalRead = 0;
    // cout << "read phase X" << endl;
    while (totalRead < toRead) {
        int result = read(buffer + totalRead, toRead-totalRead);
        // cout << "read phase " << i << " "<< result << endl;
        if (result < 0) {
            return result;
        } else {
            totalRead += result;
        }
        i++;
        // sleep(1);
    }

    return totalRead;
}

// send
int Socket::send(const void *buf, size_t len, int flags){
    return ::send(socket_fd, buf, len, flags);
}

// close
int Socket::close(){
    pthread_cancel(r_thread);
    return ::close(socket_fd);
}

int Socket::sendPacket(Packet packet){
    cout << "--- Packet sending..." << endl;
    char* buffer = (char*) packet;
    int buffer_length = packet.getSize() + 8;

    int sendResult = send(buffer, buffer_length, 0);
    
    if(sendResult < 1){
        perror("--- Packet could not send!");
    } else{
        cout << "--- Packet sent. Packet size:" << sendResult << endl;
    }

    return sendResult;
}

int Socket::readPacket(Packet& packet){
    // cout << "--- Packet is being readed..." << endl;
    // read the header first
    int HEADER_LEN = 8;
    char header[HEADER_LEN] = {0};

    int headerResult = readXBytes(header, HEADER_LEN); // read 
    // cout << "--- headerResult: " << headerResult << endl;
    if( headerResult < 1){
        // perror("--- Header could not read!");
        return headerResult;
    }

    uint32_t type = uchars_to_uint32((unsigned char*) header);
    uint32_t size = uchars_to_uint32((unsigned char*) (header+4)); // uchars_to_uint32((unsigned char*) (header+4) );
    // cout << "type:" << type << ", size:" << size << endl;
    // read the data
    char* data = new char[size];
    int readResult = readXBytes(data, size);
/*     cout << "data:";
    for(int i = 0; i < size; i++){
        cout << data[i];
    }
    cout << endl; */
    
    if(readResult < 1){
        return readResult;
        // perror("--- Packet could not read!");
    }

    packet.setType(type);
    packet.setSize(size);
    packet.setData(data);
    
    return headerResult + readResult;
}

pthread_t Socket::runReadThread(){
    pthread_create(&r_thread, NULL, (THREADFUNCPTR) &Socket::ReadThread, this);
    return r_thread;
}

void* Socket::ReadThread(){
    while(true){
        // Reading from the network buffer into socket's circular buffer
        int EMPTY_SPACE = BUFFER_LENGTH - BUFFER.size(); // available space in the circular buffer
        if( EMPTY_SPACE != 0){
            char TMP_BUFFER[EMPTY_SPACE]; // temporary buffer for retrieving data from network buffer
            // cout << "EMPTY SPACE " << EMPTY_SPACE << endl;
            int valread = ::read(socket_fd, TMP_BUFFER, EMPTY_SPACE);
            
            pthread_mutex_lock(&lock);
            BUFFER.enqueue( TMP_BUFFER, valread);
            pthread_mutex_unlock(&lock);

            // cout << "valread: " << valread << endl;
        }
    }
}