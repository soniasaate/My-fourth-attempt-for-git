#include "Hero.h"
#include <algorithm>
#include <iostream>

//Hero::Hero(const string& heroName, int heroMaxHp, int cooldown): name(heroName),  hp(heroMaxHp),  maxHp(heroMaxHp),  specialCooldown(cooldown),  turnsSinceSpecial(0),  alive(true)

Hero::Hero(const string &heroName, int heroMaxHp): name(heroName), hp(heroMaxHp), maxHp(heroMaxHp), alive(true),
     shieldHP(0),shieldRoundsLeft(0),      dopingRoundsLeft(0),
      bloodSerumRoundsLeft(0),hidden(false),hiddenRoundsLeft(0),pendingDeath(false)
{
}

void Hero::takeDamage(int damage)
{
    if (!alive || damage <= 0)
        return;
    if (shieldHP > 0)
    {
        if (damage < shieldHP)
        {
            shieldHP -= damage;

            cout << name << "'s shield absorbed "<< damage << " damage.\n";
            //shieldRoundsLeft--;
            return;
        }

        damage -= shieldHP;

        cout << name << "'s shield was destroyed.\n";

        shieldHP = 0;
        shieldRoundsLeft = 0;
    }


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
    //cout<< "Hero healing done with "<<amount<<" hp" <<endl;
    
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


void Hero::addShield(int amount, int rounds)
{
    shieldHP = amount;
    shieldRoundsLeft = rounds;
}

void Hero::decreaseShieldRound()
{
    if (shieldRoundsLeft < 0)
        return;

    shieldRoundsLeft--;

    if (shieldRoundsLeft == 0)
    {
        shieldHP = 0;
        cout << name << "'s shield expired.\n";
    }
}

bool Hero::hasShield() const
{
    return shieldHP > 0;
}

int Hero::getShieldHP() const
{
    return shieldHP;
}

void Hero::activateDoping(int rounds)
{
    dopingRoundsLeft = rounds;
}

bool Hero::hasDoping() const
{
    return dopingRoundsLeft > 0;
}

void Hero::activateBloodSerum(int rounds)
{
    bloodSerumRoundsLeft = rounds;
}

void Hero::activateHidden(int rounds)
{
    hidden = true;
    hiddenRoundsLeft = rounds;
}

void Hero::addPendingDeath()
{
    pendingDeath = true;
}

void Hero::clearNegativeEffects()
{
    pendingDeath = false;
}



void Hero::processEndOfRoundEffects()
{
    if (!alive)
        return;

    // سرم خون
    if (bloodSerumRoundsLeft > 0)
    {
        heal(40);
        bloodSerumRoundsLeft--;

        cout << name << " was healed by Blood Serum.\n";
    }

    // طاها بزرگه
    if (pendingDeath)
    {
        if(getHP()>360)
        {
            takeDamage(200);
        }
        else
        {
            takeDamage(360);
        }
        
        pendingDeath = false;

        cout << name << " was eliminated by delayed effect.\n";
    }

    if (shieldRoundsLeft > 0)
    {
        shieldRoundsLeft--;

        if (shieldRoundsLeft == 0)
        {
            shieldHP = 0;
            cout << name << "'s shield expired.\n";
        }
    }

    if (dopingRoundsLeft > 0)
        dopingRoundsLeft--;

    if (hiddenRoundsLeft > 0)
    {
        hiddenRoundsLeft--;

        if (hiddenRoundsLeft == 0)
        {
            hidden = false;
            cout << name << " is no longer hidden.\n";
        }
    }
}

bool Hero::canBeTargetedBySingleAttack() const
{
    return alive && !hidden;
}
Hero::~Hero()
{
}