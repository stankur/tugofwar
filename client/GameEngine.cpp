#include "GameEngine.h"
#include "socket.h"

#include <cstdlib>
#include <iostream>
#include <thread>
#include <string>

void GameEngine::updateView(std::string& newView) {
    system("clear");
    std::cout << newView << std::endl;
};

void GameEngine::runViewUpdater() {
    while(true) {
        char * buffer = new char[1024]();
        receiveFromServer(buffer);

        std::string bufferAsString{buffer};
        std::size_t lastDot = bufferAsString.find_last_of(".");

        if (lastDot!= std::string::npos) {
            std::size_t prevDot = bufferAsString.find_last_of(".", lastDot - 1);

            if (prevDot != std::string::npos) {
                std::string substring{bufferAsString.substr(prevDot + 1, lastDot - prevDot - 1)};
                this->updateView(substring);
            } else {
                std::string substring{bufferAsString.substr(0, lastDot)};
                this->updateView(substring);
            }

        }
        delete[] buffer;
    };
};

void GameEngine::runServerStateUpdater() {
    while(true) {
        std::cin >> std::noskipws;
        char input{};
        std::cin >> input;
        std::cout << "I got you pressing" << std::endl;
        const char* messageToSendServer {"success"};
        sendToServer(messageToSendServer, strlen(messageToSendServer));
    }
};

void GameEngine::run() {
    std::thread viewUpdaterThread {
        [&]() {
            this->runViewUpdater();
        }
    };
    std::thread serverStateUpdaterThread {
        [&]() {
            this->runServerStateUpdater();
        }
    };

    viewUpdaterThread.join();
    serverStateUpdaterThread.join();
};
