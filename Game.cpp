#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Game::Game()
    : currentRound(0), player1Starts(false)
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Game::startGame()
{
    cout << "\n*** Welcome to the Game! ***\n";

    chooseHeroes();
    chooseFirstPlayer();

    currentRound = 1;

    playGame();
}

void Game::chooseHeroes()
{
    // یه لیستی از قهرمان ها باید ارایه بدم تا کاربر انتخاب کنه
}

void Game::chooseFirstPlayer()
{
    player1Starts = (rand() % 2 == 0);

    if (player1Starts)
        cout << "Player 1 starts the game.\n";
    else
        cout << "Player 2 starts the game.\n";
}

void Game::playGame()
{
    while (player1.hasAliveHero() &&
           player2.hasAliveHero() &&
           currentRound <= 15)
    {
        cout << "\n============================\n";
        cout << "ROUND " << currentRound << '\n';
        cout << "============================\n";

        player1.setEnergy(calculateEnergy(1));
        player2.setEnergy(calculateEnergy(2));

        displayStatus();

        if (player1Starts)
        {
            playerTurn(player1, player2, true);

            if (!player2.hasAliveHero())
                break;

            playerTurn(player2, player1, false);
        }
        else
        {
            playerTurn(player2, player1, false);

            if (!player1.hasAliveHero())
                break;

            playerTurn(player1, player2, true);
        }


        // به همه ی قهرمان های هردو تیم به قدرت ویژه اش یک راند اضافه میکنیم
        for (Hero* hero : player1.getHeroes())
            if (hero->isAlive())
                hero->increaseTurnsSinceSpecial();

        for (Hero* hero : player2.getHeroes())
            if (hero->isAlive())
                hero->increaseTurnsSinceSpecial();

        checkWinner();

        currentRound++;
    }

    checkWinner();
}

void Game::playerTurn(Team& currentTeam, Team& opponentTeam, bool isPlayer1)
{
    cout << "\n--- Player " << (isPlayer1 ? 1 : 2) << "'s Turn ---\n";

    bool turnEnded = false;

    while (!turnEnded &&
           currentTeam.hasAliveHero() &&
           currentTeam.getEnergy() > 0)
    {
        displayStatus();

        cout << "\nRemaining energy: " << currentTeam.getEnergy() << '\n';

        cout << "1. Use Skill 1\n";
        cout << "2. Use Skill 2\n";
        cout << "3. Use Special Skill\n";
        cout << "4. End Turn\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        if (choice == 4)
        {
            turnEnded = true;
            cout << "Turn ended.\n";
            continue;
        }

        if (choice < 1 || choice > 4)
        {
            cout << "Invalid choice.\n";
            continue;
        }

        // منوی انتخاب قهرمان باید اضافه کنم قبلش 

    
    }

    if (currentTeam.getEnergy() <= 0)
        cout << "This team has no energy left.\n";
}

void Game::checkWinner()
{
    if (!player1.hasAliveHero() && !player2.hasAliveHero())
    {
        cout << "\n*** Draw! Both teams were eliminated. ***\n";
        return;
    }

    if (!player1.hasAliveHero())
    {
        cout << "\n*** Player 2 Wins! ***\n";
        return;
    }

    if (!player2.hasAliveHero())
    {
        cout << "\n*** Player 1 Wins! ***\n";
        return;
    }

    if (currentRound >= 15)
    {
        int alive1 = player1.aliveCount();
        int alive2 = player2.aliveCount();

        if (alive1 > alive2)
            cout << "\n*** Player 1 Wins by alive hero count! ***\n";
        else if (alive2 > alive1)
            cout << "\n*** Player 2 Wins by alive hero count! ***\n";
        else
            cout << "\n*** Draw! Both teams have equal alive heroes. ***\n";
    }
}

void Game::displayStatus()
{
    cout << "\n========== GAME STATUS ==========\n";
    cout << "Round: " << currentRound << "\n";

    cout << "\nPlayer 1 | Energy: " << player1.getEnergy() << '\n';

    for (Hero* hero : player1.getHeroes())
    {
        cout << "- " << hero->getName()
             << " [" << hero->getRole() << "]"
             << " | HP: " << hero->getHP()
             << "/" << hero->getMaxHP()
             << " | " << (hero->isAlive() ? "Alive" : "Dead")
             << '\n';
    }

    cout << "\nPlayer 2 | Energy: " << player2.getEnergy() << '\n';

    for (Hero* hero : player2.getHeroes())
    {
        cout << "- " << hero->getName()
             << " [" << hero->getRole() << "]"
             << " | HP: " << hero->getHP()
             << "/" << hero->getMaxHP()
             << " | " << (hero->isAlive() ? "Alive" : "Dead")
             << '\n';
    }

    cout << "=================================\n";
}

int Game::calculateEnergy(int playerNumber) const
{
    bool isStarter =(playerNumber == 1 && player1Starts) || (playerNumber == 2 && !player1Starts);

    if (isStarter)
    {
        if (currentRound == 1) return 5;
        if (currentRound == 2) return 8;
        if (currentRound == 3) return 9;
        return 10;
    }

    if (currentRound == 1) return 8;
    if (currentRound == 2) return 9;
    return 10;
}