#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "GameState.h"
#include <vector>

class GameEngine {
    public:
        GameEngine(GameState* gameState_, const std::vector<int>* sockets_): gameState(gameState_), sockets(sockets_){};
        void run();
    private:
        GameState* gameState;
        const std::vector<int>* sockets;
        void updateView(int pointDifference);
        void updateOpponents(int pointDifference);
        void runViewUpdater();
        void runSelfStateUpdater();
};

#endif
