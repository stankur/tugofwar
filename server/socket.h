#ifndef SOCKET_H
#define SOCKET_H
#include "GameEngine.h"

#include <cstddef>
#include <vector>
#include <thread>

void initializeSocket(std::vector<int>* sockets, GameEngine* gameEngine, bool* done, std::vector<std::thread*>* threads);
void sendToExternal(int socketId, const char* message, std::size_t messageLength);
void receiveFromExternal(int socketId);

#endif
