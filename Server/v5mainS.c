#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>


#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>

int createTPCIpv4Socket() { 
    return socket(AF_INET, SOCK_STREAM, 0);
     }

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

struct AcceptedSocket
{
    int socketFD;
    struct sockaddr_in address;
    int error;
    bool AcceptedSuccessful; 
};

struct AcceptedSocket * acceptIncomingConnection(int serverSocketFD){
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD,&clientAddress,&clientAddressSize);

    struct AcceptedSocket* acceptedSocket = malloc(sizeof (struct AcceptedSocket));
    acceptedSocket->address = clientAddress;
    acceptedSocket->socketFD = clientSocketFD;
    acceptedSocket->AcceptedSuccessful = clientSocketFD>0;

    if(!acceptedSocket->AcceptedSuccessful)
        acceptedSocket->error = clientSocketFD;

    return acceptedSocket;

};

void receiveAndPrintIncomingData(int socketFD) {
    
    char buffer[1024];

    while(true){
        ssize_t amountReceived = recv(socketFD,buffer,1024,0);

        if(amountReceived>0){
            buffer[amountReceived] = 0;
            printf("Response was %s\n ",buffer);

            sendReceivedMessageToTheOtherClients(buffer,socketFD);
        }
        if(amountReceived==0) // error handling
            break;    
    }
    

}


void StartAcceptingIncomingConnections(int serverSocketFD){

        while(true){
        struct AcceptedSocket* clientSocket = acceptIncomingConnection(serverSocketFD); // Access to client FDs
        acceptedSockets[acceptedSocketsCount++] = *clientSocket;
        ReceiveAndPrintSeparatethreads(clientSocket);
    }

}

void ReceiveAndPrintSeparatethreads(struct AcceptedSocket *pSocket){
    pthread_t id;
    pthread_create(&id,NULL,receiveAndPrintIncomingData,pSocket->socketFD);
    
}



void sendReceivedMessageToTheOtherClients(char *buffer,int socketFD) {
    for(int i=0;i<acceptedSocketsCount;i++){  // send to other users
        if(acceptedSockets[i].socketFD != socketFD)
        send(acceptedSockets[i].socketFD,buffer,strlen(buffer),0);
    }
}


struct AcceptedSocket acceptedSockets[10] ; // To record connected clients
int acceptedSocketsCount = 0;

int main() {
    int serverSocketFD = createTPCIpv4Socket();

    struct sockaddr_in* serveraddress = createIPv4Address("127.0.0.1", 2001);

    int result = bind(serverSocketFD,serveraddress,sizeof(*serveraddress));
    if(result==0)
        printf("bind was successful\n");
    
    int listenresult = listen(serverSocketFD,10); // 10 max connections

    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);

    StartAcceptingIncomingConnections(serverSocketFD);

    shutdown(serverSocketFD,SHUT_RDWR);
    

    return 0;
}
