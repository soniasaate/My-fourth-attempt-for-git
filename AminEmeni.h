#ifndef AMINEMENI_H
#define AMINEMENI_H

#include "Hero.h"

class AminEmeni : public Hero
{
public:
    AminEmeni();

    void skill1(Team& myTeam, Team& enemyTeam) override;
    void skill2(Team& myTeam, Team& enemyTeam) override;
    void specialSkill(Team& myTeam, Team& enemyTeam) override;

    string getRole() const override;

private:
    int killStreak ;
    bool dopingActive = false;
};
#endif