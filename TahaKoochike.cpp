#include "TahaKoochike.h"
#include "Team.h"
#include <iostream>

using namespace std;

TahaKoochike::TahaKoochike(): Hero("Taha Koochike", 500)
{
}

string TahaKoochike::getRole() const
{
    return "Healer";
}

void TahaKoochike::skill1(Team& myTeam, Team& enemyTeam)
{
    if (myTeam.getEnergy() < 2)
    {
        cout << "Not enough energy!\n";
        return;
    }

    myTeam.decreaseEnergy(2);
    Hero* weakestAlly = myTeam.getWeakestHero();

    if (weakestAlly != nullptr)
    {
        weakestAlly->heal(20);

        cout << weakestAlly->getName() << " was healed by 20 HP.\n";
    }

    cout << "\nChoose an enemy to damage:\n";

    Hero* targetEnemy = enemyTeam.chooseAliveHero();

    int damage =30;
    if (hasDoping())
    {
        damage = damage * 120 / 100;
    }
    targetEnemy->takeDamage(damage);

    cout << targetEnemy->getName() << " took 30 damage.\n";

    cout << "Taha Koochike used Sharp Blade.\n";
}

void TahaKoochike::skill2(Team& myTeam, Team& enemyTeam)
{
    if (myTeam.getEnergy() < 4)
    {
        cout << "Not enough energy!\n";
        return;
    }


    cout << "\nChoose an ally for Blood Serum:\n";

    Hero* ally = myTeam.chooseAliveHero();
    if (ally == nullptr)
        return;

    myTeam.decreaseEnergy(4);

    ally->activateBloodSerum(2);


    cout << ally->getName()<< " received Blood Serum.\n";

}

void TahaKoochike::specialSkill(Team& myTeam, Team& enemyTeam)
{
    if (myTeam.getEnergy() < 4)
    {
        cout << "Not enough energy!\n";
        return;
    }

    myTeam.decreaseEnergy(4);
    if (!myTeam.canUseSpecial(3))
    {
        cout << "Taha Koochike's special skill is not ready.\n";
        return;
    }

    Hero* weakestAlly = myTeam.getWeakestHero();

    if (weakestAlly == nullptr)
    {
        cout << "No alive ally is available.\n";
        return;
    }

    cout << "\"Everyone stay where you are! This area is contaminated!\"\n";

    weakestAlly->heal(200);

    cout << weakestAlly->getName()<< " was healed by 200 HP.\n";

    myTeam.resetSpecialTurns();
}