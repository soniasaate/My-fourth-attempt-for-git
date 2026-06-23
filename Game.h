#ifndef GAME_H
#define GAME_H

#include "Team.h"

class Game
{
private:
    Team player1;
    Team player2;

    int currentRound;
    bool player1Starts;

public:
    Game();

    void startGame();

    void chooseHeroes();
    void chooseFirstPlayer();

    void playGame();

    void playerTurn(Team& currentTeam, Team& opponentTeam, bool isPlayer1);

    void checkWinner();
    void displayStatus();

    int calculateEnergy(int playerNumber) const;
};

#endif