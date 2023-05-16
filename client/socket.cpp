#include "socket.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>

int PORT = 8080;
int socketId{};
std::size_t EXPECTED_SERVER_MESSAGE_SIZE_MAX = 1024;


void createSocket() 
{
    socketId = socket(AF_INET, SOCK_STREAM, 0);

    if (socketId < 0) {
        perror("failed to create socket");
        exit(EXIT_FAILURE);
    }
}

void fillWithBinaryAddress(void* toBeFilled) 
{
    int conversionResult = inet_pton(AF_INET, "127.0.0.1", toBeFilled);

    if (conversionResult < 0) {
        perror("failed to convert and fill binary address");
        exit(EXIT_FAILURE);
    }
} 

void connectToServer() {
    struct sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    fillWithBinaryAddress(&serverAddress.sin_addr);

    int connectedStatus = connect(socketId, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    if (connectedStatus < 0) {
        perror("failed to connect to server");
        exit(EXIT_FAILURE);
    }
}

void initializeSocket() {
    createSocket();
    connectToServer();
}

void sendToServer(char* message, std::size_t messageLength){
    auto sendResult  = send(socketId, message, messageLength, 0);

    if (sendResult < 0) {
        perror("failed to send to server");
        exit(EXIT_FAILURE);
    }
};

void receiveFromServer(char* buffer){

    auto readResult = read(socketId, buffer, EXPECTED_SERVER_MESSAGE_SIZE_MAX);

    if (readResult < 0) {
        perror("failed to receive from server");
        exit(EXIT_FAILURE);
    }
};


