#include "GameState.h"
#include <thread>
#include <iostream>

void GameState::incrementAllyPoints() {
    std::lock_guard<std::mutex> lock(pointsLock);
    allyPoints++;
}

void GameState::incrementOpponentPoints() {
    std::lock_guard<std::mutex> lock(pointsLock);
    opponentPoints++;
}

int GameState::getPointsDifference() {
    std::lock_guard<std::mutex> lock(pointsLock);
    return allyPoints - opponentPoints;
}

