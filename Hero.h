#ifndef HERO_H
#define HERO_H

#include <string>
using namespace std;

class Team;

class Hero
{
protected:
    string name;
    int hp;
    int maxHp;

    int specialCooldown;
    int turnsSinceSpecial;

    bool alive;

public:
    Hero(const string& heroName, int heroMaxHp, int cooldown);

    virtual void skill1(Team& myTeam, Team& enemyTeam) = 0;
    virtual void skill2(Team& myTeam, Team& enemyTeam) = 0;
    virtual void specialSkill(Team& myTeam, Team& enemyTeam) = 0;

    virtual string getRole() const = 0;

    void takeDamage(int damage);
    void heal(int amount);

    bool isAlive() const;

    int getHP() const;
    int getMaxHP() const;

    string getName() const;

    bool canUseSpecial() const;

    void increaseTurnsSinceSpecial();
    void resetTurnsSinceSpecial();

    int getTurnsSinceSpecial() const;
    int getSpecialCooldown() const;

    virtual ~Hero();
};

#endif