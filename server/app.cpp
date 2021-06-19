#include "server.h"

int main(){
    Server server = Server();
    server.run(8080);
    return 0;
}