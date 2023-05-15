#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <thread>

class GameState
{
public:
    GameState() = default;
    int getAllyPoints() { return allyPoints; };
    int getOpponentPoints(){ return opponentPoints; };
    int getPointsDifference();
    void incrementAllyPoints();
    void incrementOpponentPoints();

private:
    std::mutex pointsLock;
    int allyPoints{0};
    int opponentPoints{0};
};


#endif
