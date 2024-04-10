#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>

int createTPCIpv4Socket() { return socket(AF_INET, SOCK_STREAM, 0); }


struct sockaddr_in* createIPv4Address(char *ip, int port) {

    struct sockaddr_in  *address = malloc(sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);

    if(strlen(ip) ==0)
        address->sin_addr.s_addr = INADDR_ANY;
    else
        inet_pton(AF_INET,ip,&address->sin_addr.s_addr);

    return address;
}


int main() {
    int serverSocketFD = createTPCIpv4Socket();

    struct sockaddr_in* serveraddress = createIPv4Address("127.0.0.1", 2000);

    int result = bind(serverSocketFD,serveraddress,sizeof(*serveraddress));
    if(result==0)
        printf("bind was successful\n");
    
    int listenresult = listen(serverSocketFD,10); // 10 max connections

    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD,&clientAddress,&clientAddressSize); // Access to client FDs

    char buffer[1024];
    recv(clientSocketFD,buffer,1024,0);

    printf("Response was %s\n ",buffer);

    return 0;
}

