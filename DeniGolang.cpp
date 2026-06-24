#include "DeniGolang.h"
#include "Team.h"
#include <iostream>

//قابلیت اولش کامل نیست فقط

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
    int damage=50;
    if (hasDoping())
    {
        damage = damage * 120 / 100;
    }

    target->takeDamage(damage);
    Hero* maxhp = enemyTeam.getStrongestHero();
    maxhp->takeDamage(damage);
    cout<< "hits Maxhp enemy 50hp and hits"<< target->getName()<<"50hp\n";
    cout << "Elephant killer  skill used\n";
}


void DeniGolang::specialSkill(Team& myTeam, Team& enemyTeam)
{
    if (!myTeam.canUseSpecial(4))
    {
        cout << "Special not ready\n";
        return;
    }

    if (myTeam.getEnergy() < 4)
    {
        cout << "Not enough energy!\n";
        return;
    }
    

    Hero* shieldTarget = myTeam.getWeakestHero();
    if (shieldTarget == nullptr)
        return;

    myTeam.decreaseEnergy(4);

    shieldTarget->addShield(250, 2);


    cout <<"No one crosses this line!"<<endl;

    cout << "Shield applied to " << shieldTarget->getName() <<"for 2 round"<< endl;

    myTeam.resetSpecialTurns();
}