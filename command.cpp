#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// hexToASCII
// 

struct COMMAND{
    char type[4];
    char size[4];
    char* data;
};

int main(){
    struct COMMAND cm;
    
    printf(hexToASCII("0"));
    printf("hello \r\n");
    return 0;
}

