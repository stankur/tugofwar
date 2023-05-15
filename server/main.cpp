#include "GameState.h"
#include "GameEngine.h"

#include <iostream>
#include <vector>


int main()
{
    bool done = false;
    std::vector<int> emptySocketVector;
    GameState GameState{};

    GameEngine GameEngine{&GameState, &emptySocketVector, &done};
    GameEngine.run();

    return 0;
}
