#ifndef DENIGOLANG_H
#define DENIGOLANG_H

#include "Hero.h"


class DeniGolang : public Hero
{
public:
    DeniGolang();

    void skill1(Team& myTeam, Team& enemyTeam) override;
    void skill2(Team& myTeam, Team& enemyTeam) override;
    void specialSkill(Team& myTeam, Team& enemyTeam) override;

    string getRole() const override;

private:
    Hero* shieldTarget = nullptr;
    int shieldHP = 0;
    int shieldTurns = 0;
};


#endif