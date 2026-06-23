
#include "Team.h"
#include <algorithm>

Team::Team() : energy(0) 
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

Hero* Team::getWeakestHero() {
    Hero* weakest = nullptr;
    int minHp = INT_MAX;
    
    for (Hero* hero : heroes) {
        if (hero->isAlive() && hero->getHP() < minHp) {
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


Team::~Team()
{
    for (Hero* hero : heroes)
    {
        delete hero;
    }
}