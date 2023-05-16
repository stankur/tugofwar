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
}

void GameEngine::updateExternal(int pointDifference)
{
    std::string opponentBarView ((std::size_t) ((ROPE_LENGTH / 2) - pointDifference),'+');
    
    for (int socketId: *sockets){
        sendToExternal(socketId, &opponentBarView[0], opponentBarView.size());
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
        std::cout << "just before cin input" << std::endl;

        std::cin >> input;
        std::cout << "successfully listened" << std::endl;

        gameState->incrementAllyPoints();
    }
}

void GameEngine::runExternalStateUpdater(int socketId)
{
    while(!*done) {
        char* buffer{};
        receiveFromExternal(socketId, buffer);
        
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

    viewUpdaterThread.join();
    stateUpdaterThread.join();
}




