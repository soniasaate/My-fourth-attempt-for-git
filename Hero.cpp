#include "hero.h"

hero::hero()
{
    name = "";
    hp = 100;
    maxHp = 100;
    specialCooldown = 3;      
    turnsSinceSpecial = 0;
    alive = true;
}

void hero::takeDamage(int damage) 
{
    if (!alive) 
    return;  
    
    hp -= damage;
    if (hp < 0) 
    {
        hp = 0;
        alive = false;
    }
}

void hero::heal(int amount) 
{
    if (!alive) 
    return; 
    
    hp += amount;
    if (hp > maxHp) 
    {
        hp = maxHp;  
    }
}

bool hero::isAlive() const
{
    return alive;
}


int hero::getHP() const
{
    return hp;
}

bool hero::canUseSpecial() 
{
    return (turnsSinceSpecial >= specialCooldown);
}

void hero::increaseturnsp() 
{
    turnsSinceSpecial++;
}

void hero::resetturnspr()
{
    turnsSinceSpecial=0;
}

hero::~hero()
{
}