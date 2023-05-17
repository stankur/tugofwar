#include "GameState.h"
#include "GameEngine.h"
#include "socket.h"

#include <iostream>
#include <vector>
#include <thread>

int main()
{
    std::vector<int> sockets;
    bool done{false};
    GameState GameState{};

    std::vector<std::thread*> threads{};

    GameEngine GameEngine{&GameState, &sockets, &done};
    initializeSocket(&sockets, &GameEngine, &done, &threads);

    GameEngine.run();

    for (std::thread* thread: threads) {
        thread->join();
    }

    for (std::thread* thread: threads) {
        delete thread;
    }

    return 0;
}
