#include "socket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>



int PORT = 8080;
int MAXIMUM_SOCKET_CONNECTIONS = 3;

#ifdef __APPLE__

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int socketId{};

void createSocket() 
{
    std::cout << "just entered" << std::endl;
    socketId = socket(AF_INET, SOCK_STREAM, 0);

    if (socketId < 0) {
        perror("failed to create socket");
        exit(EXIT_FAILURE);
    }

    std::cout << socketId;
}


struct sockaddr_in address{};

void bindSocketToPort()
{
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int bindingResult = bind(socketId,(sockaddr *) &address, sizeof(address));

    if (bindingResult < 0) {
        std::cout << socketId;

        perror("failed to bind socket to port");
        exit(EXIT_FAILURE);
    }
    std::cout << "yo bounded" << std::endl;

}

void startListening()
{
    int listeningResult = listen(socketId, MAXIMUM_SOCKET_CONNECTIONS);

    if (listeningResult < 0) {
        perror("failed to listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "yo listening" << std::endl;
}

void startAccepting()
{
    int newSocket = accept(socketId, nullptr, nullptr);

    if (newSocket < 0) {
        perror("failed to accept connection");
        exit(EXIT_FAILURE);
    } else {
        std::cout << "yo connected" << std::endl;
    }
}

void initializeSocket()
{
    createSocket();
    bindSocketToPort();
    startListening();
    startAccepting();
}

#else

#endif
