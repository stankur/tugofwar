#include "socket.h"
#include "GameEngine.h"

int main() {
    initializeSocket();
    GameEngine GameEngine;
    GameEngine.run();

    return 0;
}
