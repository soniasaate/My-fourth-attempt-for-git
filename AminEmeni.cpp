#include "AminEmeni.h"
#include "Team.h"

AminEmeni::AminEmeni(): Hero("Amin Emeni", 500)
{
}

void AminEmeni::skill1(Team& myTeam, Team& enemyTeam)
{
    if (myTeam.getEnergy() < 3)
    {
        cout << "Not enough energy!\n";
        return;
    }

    myTeam.decreaseEnergy(3);
    Hero* target = enemyTeam.getRandomAliveHero();
    if (!target) return;

    int damage = 55 * killStreak;

    target->takeDamage(damage);
//ناقص و اشتباه نوشتم
    if (!target->isAlive())
        killStreak *= 2;

    cout << "Amin hit " << damage << endl;
    cout << "Last bullet used skill used"<<endl;
}


void AminEmeni::skill2(Team& myTeam, Team& enemyTeam)
{
    if (myTeam.getEnergy() < 3)
    {
        cout << "Not enough energy!\n";
        return;
    }

    myTeam.decreaseEnergy(3);
    Hero* ally = myTeam.getRandomAliveHero();
    while (ally == this) 
    {
        ally = myTeam.getRandomAliveHero(); 
    }

    if (!ally) return;

    ally->takeDamage(25);
    this->heal(75);

    cout << "Amin used self-hit skill\n";
}

void AminEmeni::specialSkill(Team& myTeam, Team& enemyTeam)
{
    if (myTeam.getEnergy() < 4)
    {
        cout << "Not enough energy!\n";
        return;
    }
    myTeam.decreaseEnergy(4);
    if (!myTeam.canUseSpecial(3))
    {
        cout << "Not ready\n";
        return;
    }

    Hero* target = enemyTeam.getRandomAliveHero();

    if (!target) return;

    cout<<"One.. two... three.. boom... who's left? It doesn't matter."<<endl;

    int damage = 250;

    /*if (dopingActive)
        damage = damage * 1.2;*/
    target->takeDamage(damage);

    vector<Hero*>& heroes = myTeam.getHeroes();

    for (int i = 0; i < heroes.size(); i++)
    {
        if (heroes[i] != this)
          heroes[i]->takeDamage(20);
    }

    myTeam.resetSpecialTurns();
}