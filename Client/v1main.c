#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


int main() {
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);

    char* ip = "142.250.188.46";
    struct sockaddr_in address ;
    address.sin_family = AF_INET; // IPV4
    address.sin_port = htons(80); // usually reserved under 1000 big/little endian
    address.sin_addr.s_addr = inet_pton(AF_INET,ip,&address.sin_addr.s_addr); // present to netw

    int result = connect(socketFD,&address,sizeof(address));

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