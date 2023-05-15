#ifndef SOCKET_H
#define SOCKET_H

#include <cstddef>

void initializeSocket();

long sendToOpponent(int socketId, char* message, std::size_t messageLength);

#endif




