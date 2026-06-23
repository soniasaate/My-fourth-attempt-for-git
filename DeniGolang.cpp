#include "DeniGolang.h"
#include "Team.h"
#include <iostream>

using namespace std;

DeniGolang::DeniGolang(): Hero("Deni Golang", 600)
{

}

string DeniGolang::getRole() const
{
    return "Defender";
}

void DeniGolang::skill1(Team& myTeam, Team& enemyTeam)
{
     if (myTeam.getEnergy() < 2)
    {
        cout << "Not enough energy!\n";
        return;
    }

    myTeam.decreaseEnergy(2);
    Hero* target = enemyTeam.getRandomAliveHero();

    if (!target) return;

    static float multiplier = 1;

    float damage = 20 * multiplier;
    target->takeDamage(damage);

    //multiplier *= 1.6;

    cout << "Deni Golang lock skill used , he hits" <<damage << endl;
}


void DeniGolang::skill2(Team& myTeam, Team& enemyTeam)
{
    if (myTeam.getEnergy() < 4)
    {
        cout << "Not enough energy!\n";
        return;
    }

    myTeam.decreaseEnergy(4);
    Hero* target = enemyTeam.chooseAliveHero();
    Hero* maxhp = enemyTeam.getStrongestHero();

    target->takeDamage(50);
    maxhp->takeDamage(50);

    cout << "Elephant killer  skill used\n";
}


void DeniGolang::specialSkill(Team& myTeam, Team& enemyTeam)
{
        if (myTeam.getEnergy() < 4)
    {
        cout << "Not enough energy!\n";
        return;
    }
    myTeam.decreaseEnergy(4);

    if (!myTeam.canUseSpecial(4))
    {
        cout << "Special not ready\n";
        return;
    }

    shieldTarget = myTeam.getWeakestHero();
    cout <<"No one crosses this line!"<<endl;

    if (!shieldTarget) return;
    //باید سپر رو توی کلاس قهرمان اضافه کنم
    shieldHP = 250;
    shieldTurns = 2;

    cout << "Shield applied to " << shieldTarget->getName() << endl;

    myTeam.resetSpecialTurns();
}