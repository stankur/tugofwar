#include "socket.h"
#include "GameEngine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstddef> 
#include <vector>
#include <thread>

int PORT = 8080;
int MAXIMUM_SOCKET_CONNECTIONS = 3;
std::size_t EXPECTED_EXTERNAL_MESSAGE_SIZE_MAX = 1024;

#ifdef __APPLE__

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int socketId{};

void createSocket() 
{
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

}

void startListening()
{
    int listeningResult = listen(socketId, MAXIMUM_SOCKET_CONNECTIONS);

    if (listeningResult < 0) {
        perror("failed to listen");
        exit(EXIT_FAILURE);
    }
}

void startAccepting(std::vector<int>* sockets, GameEngine* gameEngine, bool* done, std::vector<std::thread*>* threads)
{
    while (static_cast<int>(sockets->size()) < MAXIMUM_SOCKET_CONNECTIONS && !*done) {
        int newSocket = accept(socketId, nullptr, nullptr);

        if (newSocket < 0) {
            perror("failed to accept connection");
            exit(EXIT_FAILURE);
        } else {
            sockets->push_back(newSocket);

            std::thread* externalStateUpdater = new std::thread(
                [&](){
                    gameEngine->runExternalStateUpdater(newSocket);
                }
            );
            std::thread* externalViewUpdater = new std::thread(
                [&](){
                    gameEngine->updateExternal(newSocket);
                }
            );

            threads->push_back(externalStateUpdater);
            threads->push_back(externalViewUpdater);
        }
    }
}

void initializeSocket(std::vector<int>* sockets, GameEngine* gameEngine, bool* done, std::vector<std::thread*>* threads)
{
    createSocket();
    bindSocketToPort();
    startListening();
    std::thread* acceptingConnectionsThread = new std::thread(startAccepting, sockets, gameEngine, done, threads);
    threads->push_back(acceptingConnectionsThread);
}

void sendToExternal(int socketId, const char* message, size_t messageLength)
{
    auto result = send(socketId, message, messageLength, 0);
    if (result < 0) {
        perror("failed to send to external");
        exit(EXIT_FAILURE);
    }
};

void receiveFromExternal(int socketId){
    char * buffer = new char[EXPECTED_EXTERNAL_MESSAGE_SIZE_MAX]();

    while(read(socketId, buffer, EXPECTED_EXTERNAL_MESSAGE_SIZE_MAX) <= 0) {
        // just loops and blocks until message is received
    }

    delete[] buffer;

};


#else

#endif
