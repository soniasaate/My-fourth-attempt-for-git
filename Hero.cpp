#include "Hero.h"
#include <algorithm>
#include <iostream>

//Hero::Hero(const string& heroName, int heroMaxHp, int cooldown): name(heroName),  hp(heroMaxHp),  maxHp(heroMaxHp),  specialCooldown(cooldown),  turnsSinceSpecial(0),  alive(true)

Hero::Hero(const string &heroName, int heroMaxHp): name(heroName), hp(heroMaxHp), maxHp(heroMaxHp), alive(true)
{
}

void Hero::takeDamage(int damage)
{
    if (!alive || damage <= 0)
        return;

    hp -= damage;

    if (hp <= 0)
    {
        hp = 0;
        alive = false;
    }
}

void Hero::heal(int amount)
{
    if (!alive || amount <= 0)
        return;

    hp += amount;

    if (hp > maxHp)
    {
        hp = maxHp;
    }
    cout<< "Hero healing done with "<<amount<<" hp" <<endl;
    
}

bool Hero::isAlive() const
{
    return alive;
}

int Hero::getHP() const
{
    return hp;
}

int Hero::getMaxHP() const
{
    return maxHp;
}

string Hero::getName() const
{
    return name;
}

/*bool Hero::canUseSpecial() const
{
    return turnsSinceSpecial >= specialCooldown;
}

void Hero::increaseTurnsSinceSpecial()
{
    if (!canUseSpecial())
        turnsSinceSpecial++;
}

void Hero::resetTurnsSinceSpecial()
{
    turnsSinceSpecial = 0;
}

int Hero::getTurnsSinceSpecial() const
{
    return turnsSinceSpecial;
}

int Hero::getSpecialCooldown() const
{
    return specialCooldown;
}*/

void Hero::revive(int amount)
{
    if (alive)
        return;

    alive = true;
    hp = amount;

    if (hp > maxHp)
        hp = maxHp;
}

Hero::~Hero()
{
}