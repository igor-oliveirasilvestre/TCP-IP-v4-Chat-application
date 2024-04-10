#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>


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

struct AcceptdedSocket
{
    int socketFD;
    struct sockaddr_in address;
    int error;
    bool AcceptedSuccessful;
};


int main() {
    int socketFD = createTPCIpv4Socket();  // create socket

    struct sockaddr_in *address = createIPv4Address("127.0.0.1", 2001); // create address test "142.250.188.46", 80
 
    int result = connect(socketFD,address,sizeof(*address)); 

    if (result == 0)
        printf("connection was successful\n");  

    char* line = NULL;
    size_t linesize = 0;
    printf("type to send (type exit)...\n");

    while(true)
    {
        ssize_t  charCount = getline(&line,&linesize,stdin);	// read from console

        if(charCount>0)
        { 
            if(strcmp(line,"exit\n")==0)
                break;

            ssize_t ammountWasSent = send(socketFD,line,charCount,0);
        }
        
    }
    close(socketFD);



 


    //port 80 http 443 httpscomm




    return 0;

}

