#include "client.h"

int main(){
    Client client = Client();
    client.run(8080);
    return 0;
}