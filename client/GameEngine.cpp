#include "GameEngine.h"
#include "socket.h"

#include <cstdlib>
#include <iostream>

void GameEngine::updateView(char* newView) {
    system("clear");
    std::cout << newView << std::endl;
};

void GameEngine::runViewUpdater() {
    while(true) {
        char* buffer{};
        receiveFromServer(buffer);
        std::cout << buffer;
    }
}

void GameEngine::runServerStateUpdater() {
    while(true) {
        std::cin >> std::noskipws;
        char input{};
        std::cin >> input;
    }
}




