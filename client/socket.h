#ifndef SOCKET_H
#define SOCKET_H

#include <cstdlib>

void initializeSocket();
void sendToServer(const char* message, std::size_t messageLength);
void receiveFromServer(char* buffer);

#endif
