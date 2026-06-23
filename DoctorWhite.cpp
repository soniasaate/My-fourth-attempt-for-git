#include "DoctorWhite.h"
#include "Team.h"
#include <iostream>

using namespace std;

DoctorWhite::DoctorWhite(): Hero("Doctor White", 550)
{
}

string DoctorWhite::getRole() const
{
    return "Healer";
}

// اسپرین دکتر که ۴۰ واحد سلامتی قهرمان رندوم خودمون افزایش و مال دشمن قهرمان انتخاب و ۴۰ تا ازش کم
void DoctorWhite::skill1(Team& myTeam, Team& enemyTeam)
{
    if (myTeam.getEnergy() < 3)
    {
        cout << "Not enough energy!\n";
        return;
    }

    myTeam.decreaseEnergy(3);
    Hero* randomAlly = myTeam.getRandomAliveHero();

    if (randomAlly != nullptr)
    {
        randomAlly->heal(40);

       cout << randomAlly->getName() << " was healed by 40 HP.\n";

    }

    cout << "\nChoose an enemy to damage:\n";

    Hero* targetEnemy = enemyTeam.chooseAliveHero();

    targetEnemy->takeDamage(40);

    cout << targetEnemy->getName() << " took 40 damage.\n";

    cout << "Doctor White used Aspirin.\n";
}

// قدرت دوم قدرت دوپینگ
void DoctorWhite::skill2(Team& myTeam, Team& enemyTeam)
{
    if (myTeam.getEnergy() < 4)
    {
        cout << "Not enough energy!\n";
        return;
    }

   Hero* ally = myTeam.chooseAliveHero();

    if (ally == nullptr)
        return;

    myTeam.decreaseEnergy(4);

    ally->activateDoping(2);

    cout << "Doctor White used Doping on " << ally->getName() << ".\n";

}

//قدرت ویژه
void DoctorWhite::specialSkill(Team& myTeam, Team& enemyTeam)
{
    if (!myTeam.canUseSpecial(4))
    {
        cout << "Doctor White's special skill is not ready.\n";
        return;
    }
    if (myTeam.getEnergy() < 4)
    {
        cout << "Not enough energy!\n";
        return;
    }


    //تمام اثرات منفی رو پاک نکردم هنوز


    Hero* deadHero = myTeam.chooseDeadHeroExcept(this);

    if (deadHero == nullptr)
    {
        return;
    }
    myTeam.decreaseEnergy(4);
    cout << "\"Bring him to the table... he may survive if lucky.\"\n";

    deadHero->revive(200);
    deadHero->clearNegativeEffects();

    cout << deadHero->getName()<< " was revived with 200 HP.\n";

    myTeam.resetSpecialTurns();
}
