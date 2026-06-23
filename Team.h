#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "Hero.h"

using namespace std;

class Team
{
private:
    vector<Hero*> heroes;
    int energy;

public:
    Team();

    void addHero(Hero* hero);

    vector<Hero*>& getHeroes();

    int getEnergy() const;

    void setEnergy(int energyAmount);

    void decreaseEnergy(int amount);

    bool hasAliveHero() const;

    int aliveCount() const;

    Hero* getWeakestHero();

    Hero* getStrongestHero();


    Hero* getRandomAliveHero();

    
    ~Team();
};

#endif