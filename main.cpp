#include "GameState.h"
#include "GameEngine.h"

#include <iostream>
#include <vector>


int main()
{
    std::vector<int> emptySocketVector;
    GameState GameState{};

    GameEngine GameEngine{&GameState, &emptySocketVector};
    GameEngine.run();

    return 0;
}
