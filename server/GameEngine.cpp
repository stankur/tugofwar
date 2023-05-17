#include "GameEngine.h"

#include "socket.h"

#include <iostream>
#include <string>
#include <thread>
#include <cmath>
#include <cstdlib>

const int WINNING_POINTS_DIFFERENCE = 50;
const int ROPE_LENGTH = 100;

void GameEngine::updateView(int pointDifference) 
{
    system("clear");
    std::string barView ((std::size_t) ((ROPE_LENGTH / 2) + pointDifference), '+');
    std::cout << barView << std::endl;

    for (int socket: *sockets) {
        std::cout << socket << std::endl;
    }

}

void GameEngine::updateExternal(int pointDifference)
{
    std::string opponentBarView ((std::size_t) ((ROPE_LENGTH / 2) - pointDifference),'+');
    opponentBarView.append(".");
    const char* opponentBarViewAsCharStar = opponentBarView.c_str();

    for (int connectedSocketId: *sockets){
        sendToExternal(connectedSocketId, opponentBarViewAsCharStar, strlen(opponentBarViewAsCharStar));
    }
}

void GameEngine::runExternalUpdater() {
    while(!*done) {
        this->updateExternal(gameState->getPointsDifference());
    }
}

void GameEngine::runViewUpdater()
{
    while(std::abs(gameState->getPointsDifference()) < WINNING_POINTS_DIFFERENCE) {
        int pointDifference{gameState->getPointsDifference()};
        this->updateView(pointDifference);
    }

    *done = true;
}


void GameEngine::runSelfStateUpdater() 
{
    while(!*done) {
        std::cin >> std::noskipws;
        char input{};
        std::cin >> input;
        gameState->incrementAllyPoints();
    }
}

void GameEngine::runExternalStateUpdater(int socketId)
{
    while(!*done) {
        receiveFromExternal(socketId);

        gameState->incrementOpponentPoints();
    }
}

void GameEngine::run() 
{
    std::thread viewUpdaterThread {
        [&](){
            this->runViewUpdater();
        }
    };

    std::thread stateUpdaterThread {
        [&](){
            this->runSelfStateUpdater();
        }
    };

    std::thread externalUpdaterThread {
        [&](){
            this->runExternalUpdater();
        }
    };

    viewUpdaterThread.join();
    stateUpdaterThread.join();
    externalUpdaterThread.join();
}




