#include "AminEmeni.h"
#include "Team.h"

AminEmeni::AminEmeni(): Hero("Amin Emeni", 500),killStreak(1)
{
}

string AminEmeni::getRole() const
{
    return "Attacker";
}
void AminEmeni::skill1(Team& myTeam, Team& enemyTeam)
{
    if (myTeam.getEnergy() < 3)
    {
        cout << "Not enough energy!\n";
        return;
    }

    
    Hero* target = enemyTeam.getRandomAliveHero();
    if (!target) return;
    myTeam.decreaseEnergy(3);
    int damage = 55 * killStreak;
    if (hasDoping())
    {
        damage = damage * 120 / 100;
    }

    target->takeDamage(damage);
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
    Hero* ally = myTeam.getRandomAliveHeroExcept(this);
    if (ally == nullptr)
    {
        cout << "No other alive ally is available.\n";
        return;
    }

    ally->takeDamage(25);
    this->heal(75);

    cout << ally->getName() << " took 25 damage.\n";    
    cout << "Amin used self-hit skill\n";
}

void AminEmeni::specialSkill(Team& myTeam, Team& enemyTeam)
{
    if (!myTeam.canUseSpecial(3))
    {
        cout << "Not ready\n";
        return;
    }
    if (myTeam.getEnergy() < 4)
    {
        cout << "Not enough energy!\n";
        return;
    }



    Hero* target = enemyTeam.getRandomAliveHero();

    if (!target) return;
    myTeam.decreaseEnergy(4);

    cout<<"One.. two... three.. boom... who's left? It doesn't matter."<<endl;

    int damage = 250;
    if (hasDoping())
    {
        damage = damage * 120 / 100;
    }

    target->takeDamage(damage);

    vector<Hero*>& heroes = myTeam.getHeroes();

    for (int i = 0; i < heroes.size(); i++)
    {
        if (heroes[i] != this)
          heroes[i]->takeDamage(20);
    }

    myTeam.resetSpecialTurns();
}


