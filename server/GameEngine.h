#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "GameState.h"
#include <vector>

class GameEngine {
    public:
        GameEngine(GameState* gameState_, const std::vector<int>* sockets_, bool* done_): gameState(gameState_), done(done_), sockets(sockets_){};
        void run();
        void runExternalStateUpdater(int socketId);
        
    private:
        GameState* gameState;
        bool* done;
        const std::vector<int>* sockets;
        void updateView(int pointDifference);
        void updateExternal(int pointDifference);
        void runViewUpdater();
        void runSelfStateUpdater();
};

#endif
