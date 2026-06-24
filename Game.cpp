#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "DoctorWhite.h"
#include "TahaKoochike.h"
#include "DeniGolang.h"
#include "AminEmeni.h"
#include "TahaBozorge.h"
#include <vector>

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
    const int HEROES_PER_TEAM = 3;

    cout << "\n===== HERO SELECTION =====\n";

    cout << "\nAvailable heroes:\n";
    cout << "1. Doctor White  (Healer)\n";
    cout << "2. Taha Koochike (Support)\n";
    cout << "3. Deni Golang   (Defender)\n";
    cout << "4. Amin Emeni    (Attacker)\n";
    cout << "5. Taha Bozorge   (Attacker)\n";

    
    auto chooseForTeam = [&](Team& team, int teamNumber)
    {
        vector<int> chosenHeroes;

        cout << "\n--- Team " << teamNumber
             << ": choose " << HEROES_PER_TEAM << " heroes ---\n";

        while (chosenHeroes.size() < HEROES_PER_TEAM)
        {
            int choice;

            cout << "Choose hero " << chosenHeroes.size() + 1 << ": ";
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');

                cout << "Invalid input. Enter a number from 1 to 5.\n";
                continue;
            }

            if (choice < 1 || choice > 5)
            {
                cout << "Invalid choice. Enter a number from 1 to 5.\n";
                continue;
            }

            bool alreadyChosen = false;

            for (int heroNumber : chosenHeroes)
            {
                if (heroNumber == choice)
                {
                    alreadyChosen = true;
                    break;
                }
            }

            if (alreadyChosen)
            {
                cout << "This hero is already in your team.\n";
                continue;
            }

            Hero* newHero = nullptr;

            switch (choice)
            {
                case 1:
                    newHero = new DoctorWhite();
                    break;

                case 2:
                    newHero = new TahaKoochike();
                    break;

                case 3:
                    newHero = new DeniGolang();
                    break;

                case 4:
                    newHero = new AminEmeni();
                    break;

                case 5:
                    newHero = new TahaBozorge();
                    break;
            }

            if (newHero != nullptr)
            {
                team.addHero(newHero);
                chosenHeroes.push_back(choice);

                cout << newHero->getName()
                     << " was added to Team "
                     << teamNumber << ".\n";
            }
        }
    };

    chooseForTeam(player1, 1);
    chooseForTeam(player2, 2);

    cout << "\n===== HEROES SELECTED =====\n";

    cout << "\nTeam 1:\n";
    for (Hero* hero : player1.getHeroes())
    {
        cout << "- " << hero->getName()
             << " [" << hero->getRole() << "]"
             << " | HP: " << hero->getHP() << '\n';
    }

    cout << "\nTeam 2:\n";
    for (Hero* hero : player2.getHeroes())
    {
        cout << "- " << hero->getName()
             << " [" << hero->getRole() << "]"
             << " | HP: " << hero->getHP() << '\n';
    }
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

       // displayStatus();

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

        cout << "\n========== END OF ROUND STATUS ==========\n";
        displayStatus();

        for (Hero* hero : player1.getHeroes())
        {
           hero->processEndOfRoundEffects();
        }

        for (Hero* hero : player2.getHeroes())
        {
            hero->processEndOfRoundEffects();
        }


        //به شمارنده ی قدرت ویژه یکی اضافه میکنم
        player1.increaseSpecialTurns();
        player2.increaseSpecialTurns();

        checkWinner();

        currentRound++;
    }

    checkWinner();
}

void Game::playerTurn(Team& currentTeam, Team& opponentTeam, bool isPlayer1)
{
    int playerNumber = isPlayer1 ? 1 : 2;
    bool turnEnded = false;

    cout << "\n====================================\n";
    cout << "          PLAYER " << playerNumber << "'S TURN\n";
    cout << "====================================\n";

    while (!turnEnded &&
           currentTeam.hasAliveHero() &&
           currentTeam.getEnergy() > 0)
    {
        cout << "\nYour Team | Energy: "
             << currentTeam.getEnergy() << "\n";

        cout << "------------------------------------\n";
        cout << "Choose a hero:\n";

        vector<Hero*> aliveHeroes;

        for (Hero* hero : currentTeam.getHeroes())
        {
            if (hero->isAlive())
            {
                aliveHeroes.push_back(hero);
            }
        }

        for (int i = 0; i < static_cast<int>(aliveHeroes.size()); i++)
        {
            cout << i + 1 << ". "
                 << aliveHeroes[i]->getName()
                 << " [" << aliveHeroes[i]->getRole() << "]"
                 << " | HP: " << aliveHeroes[i]->getHP()
                 << "/" << aliveHeroes[i]->getMaxHP()
                 << '\n';
        }

        cout << aliveHeroes.size() + 1 << ". End Turn\n";
        cout << "Hero choice: ";

        int heroChoice;
        cin >> heroChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        // پایان نوبت
        if (heroChoice == static_cast<int>(aliveHeroes.size()) + 1)
        {
            turnEnded = true;
            cout << "Player " << playerNumber << " ended the turn.\n";
            break;
        }

        if (heroChoice < 1 ||
            heroChoice > static_cast<int>(aliveHeroes.size()))
        {
            cout << "Invalid hero choice.\n";
            continue;
        }

        Hero* selectedHero = aliveHeroes[heroChoice - 1];

        bool chooseAnotherHero = false;

        while (!chooseAnotherHero &&
               !turnEnded &&
               currentTeam.getEnergy() > 0)
        {
            cout << "\n------------------------------------\n";
            cout << "Selected Hero: " << selectedHero->getName()
                 << " [" << selectedHero->getRole() << "]\n";

            cout << "HP: " << selectedHero->getHP()
                 << "/" << selectedHero->getMaxHP() << '\n';

            cout << "Team Energy: " << currentTeam.getEnergy() << "\n\n";

            cout << "1. Use Skill 1\n";
            cout << "2. Use Skill 2\n";
            cout << "3. Use Special Skill\n";
            cout << "4. Choose Another Hero\n";
            cout << "5. End Turn\n";
            cout << "Skill choice: ";

            int skillChoice;
            cin >> skillChoice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input.\n";
                continue;
            }

            if (skillChoice == 4)
            {
                chooseAnotherHero = true;
                continue;
            }

            if (skillChoice == 5)
            {
                turnEnded = true;
                cout << "Player " << playerNumber << " ended the turn.\n";
                continue;
            }

            if (skillChoice < 1 || skillChoice > 5)
            {
                cout << "Invalid skill choice.\n";
                continue;
            }

            
            if (!selectedHero->isAlive())
            {
                cout << "This hero is dead and cannot use a skill.\n";
                chooseAnotherHero = true;
                continue;
            }

            int energyBefore = currentTeam.getEnergy();

            if (skillChoice == 1)
            {
                selectedHero->skill1(currentTeam, opponentTeam);
            }
            else if (skillChoice == 2)
            {
                selectedHero->skill2(currentTeam, opponentTeam);
            }
            else if (skillChoice == 3)
            {
                selectedHero->specialSkill(currentTeam, opponentTeam);
            }

            
            if (!opponentTeam.hasAliveHero())
            {
                return;
            }

        
            if (currentTeam.getEnergy() == energyBefore)
            {
                cout << "No energy was used. Choose again.\n";
            }
        }
    }

    if (currentTeam.getEnergy() <= 0)
    {
        cout << "\nPlayer " << playerNumber
             << " has no energy left. Turn ended.\n";
    }
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