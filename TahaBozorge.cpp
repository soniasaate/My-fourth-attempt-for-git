#include "TahaBozorge.h"
#include "Team.h"

TahaBozorge::TahaBozorge() : Hero ("Taha Bozorge" ,500)
{
}

void TahaBozorge::skill1(Team &myTeam, Team &enemyTeam)
{
    if (myTeam.getEnergy() < 3)
    {
        cout << "Not enough energy!\n";
        return;
    }
    myTeam.decreaseEnergy(3);

    vector<Hero*>& heroes = enemyTeam.getHeroes();

    for (int i = 0; i < heroes.size(); i++)
    {
        heroes[i]->takeDamage(30);
    }

    cout<<"the barrage skill used"<<endl;
}

void TahaBozorge::skill2(Team &myTeam, Team &enemyTeam)
{
    if (myTeam.getEnergy() < 4)
    {
        cout << "Not enough energy!\n";
        return;
    }
    myTeam.decreaseEnergy(4);  
    
    Hero* target = enemyTeam.getRandomAliveHero();

    if (!target) return;

    target->takeDamage(90);
    //پنهان شدن برای یک راند و لحاظ کردن اسیب جمعی

    cout<<"the XRay skill used"<<endl;    
}

void TahaBozorge::specialSkill(Team& myTeam, Team& enemyTeam)
{
    if (myTeam.getEnergy() < 3)
    {
        cout << "Not enough energy!\n";
        return;
    }
    myTeam.decreaseEnergy(3); 

    if (!myTeam.canUseSpecial(4))
        return;

    Hero* target = enemyTeam.getRandomAliveHero();
    if (!target) return;
    //یه حریف تو تارگت کنم و با توجه به شروط از جونش کم کنم

    cout << "Target marked for next round\n";

    myTeam.resetSpecialTurns();
}