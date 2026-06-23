#ifndef TAHABOZORGE_H
#define TAHABOZORGE_H

#include "Hero.h"

class TahaBozorge : public Hero
{
public:
    TahaBozorge();

    void skill1(Team& myTeam, Team& enemyTeam) override;
    void skill2(Team& myTeam, Team& enemyTeam) override;
    void specialSkill(Team& myTeam, Team& enemyTeam) override;

    string getRole() const override;
};

#endif