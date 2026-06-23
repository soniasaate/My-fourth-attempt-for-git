
#include "Team.h"
#include <algorithm>
#include <climits> 
#include <cstdlib>
#include <iostream>
Team::Team() : energy(0) , specialTurnsPassed(0)
{
}

void Team::addHero(Hero* hero) {
    heroes.push_back(hero);
}

vector<Hero*>& Team::getHeroes() {
    return heroes;
}

int Team::getEnergy() const {
    return energy;
}

void Team::setEnergy(int e) {
    energy = e;
}

void Team::decreaseEnergy(int amount) {
    if (energy >= amount) {
        energy -= amount;
    } else {
        energy = 0;
    }
}

bool Team::hasAliveHero() const {
    for (Hero* hero : heroes) {
        if (hero->isAlive()) {
            return true;
        }
    }
    return false;
}

int Team::aliveCount() const {
    int count = 0;
    for (Hero* hero : heroes) {
        if (hero->isAlive()) {
            count++;
        }
    }
    return count;
}

Hero* Team::getWeakestHero() 
{
    Hero* weakest = nullptr;
    int minHp = INT_MAX; //برابر بزرگتریم عدد ممکن گذاشتم که حتما قهرمان اولی که بررسی میشه رو در نظر بگیره
    
    for (Hero* hero : heroes) 
    {
        if (hero->isAlive() && hero->getHP() < minHp) 
        {
            minHp = hero->getHP();
            weakest = hero;
        }
    }
    return weakest;
}

Hero* Team::getRandomAliveHero() {
    vector<Hero*> aliveHeroes;
    for (Hero* hero : heroes) {
        if (hero->isAlive()) {
            aliveHeroes.push_back(hero);
        }
    }
    
    if (aliveHeroes.empty()) {
        return nullptr;
    }
    
    int randomIndex = rand() % aliveHeroes.size();
    return aliveHeroes[randomIndex];
}

Hero* Team::chooseAliveHero()
{
    int choice;

    while (true)
    {
        cout << "\nChoose a target:\n";

        for (int i = 0; i < heroes.size(); i++)
        {
            cout << i + 1 << ". "
                 << heroes[i]->getName()
                 << " | HP: " << heroes[i]->getHP()
                 << " | " << (heroes[i]->isAlive() ? "Alive" : "Dead")
                 << '\n';
        }

        cout << "Choice: ";
        cin >> choice;

        if (choice >= 1 &&
            choice <= heroes.size() &&
            heroes[choice - 1]->isAlive())
        {
            return heroes[choice - 1];
        }

        cout << "Invalid choice. Choose an alive hero.\n";
    }
}

Hero* Team::getStrongestHero() {
    Hero* strongest = nullptr;
    int maxHp = 0;
    
    for (Hero* hero : heroes) {
        if (hero->isAlive() && hero->getHP() > maxHp) {
            maxHp = hero->getHP();
            strongest = hero;
        }
    }
    return strongest;
}

Hero* Team::chooseDeadHeroExcept(Hero* excludedHero)
{
    vector<Hero*> deadHeroes;

    for (Hero* hero : heroes)
    {
        if (!hero->isAlive() && hero != excludedHero)
        {
            deadHeroes.push_back(hero);
        }
    }

    if (deadHeroes.empty())
    {
        cout << "There is no dead hero available \n";
        return nullptr;
    }

    cout << "\nChoose a dead hero :\n";

    for (int i = 0; i < deadHeroes.size(); i++)
    {
        cout << i + 1 << ". "<< deadHeroes[i]->getName() << " [" << deadHeroes[i]->getRole() << "]" << " | Dead\n";
    }

    int choice;

    while (true)
    {
        cout << "Choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= deadHeroes.size())
        {
            return deadHeroes[choice - 1];
        }

        cout << "Invalid choice. Try again.\n";
    }
}

void Team::increaseSpecialTurns()
{
    specialTurnsPassed++;
}

void Team::resetSpecialTurns()
{
    specialTurnsPassed = 0;
}

int Team::getSpecialTurnsPassed() const
{
    return specialTurnsPassed;
}

bool Team::canUseSpecial(int neededRounds) const
{
    return specialTurnsPassed >= neededRounds;
}


Team::~Team()
{
    for (Hero* hero : heroes)
    {
        delete hero;
    }
}