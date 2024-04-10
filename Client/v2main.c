#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

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
    int socketFD = createTPCIpv4Socket();  // create socket

    struct sockaddr_in *address = createIPv4Address("127.0.0.1", 2000); // create address test "142.250.188.46", 80
 
    int result = connect(socketFD,address,sizeof(*address)); 

    if (result == 0)
        printf("connection was successful\n");  

    char* message;
    message ="GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
    send(socketFD,message,strlen(message),0);

    char buffer[1024];
    recv(socketFD,buffer,1024,0);

    printf("Response was %s\n ",buffer);

    //port 80 http 443 httpscomm




    return 0;

}

