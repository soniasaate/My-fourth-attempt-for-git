#ifndef TAHA_KOOCHIKE_H
#define TAHA_KOOCHIKE_H

#include "Hero.h"

class TahaKoochike : public Hero
{
public:
    TahaKoochike();

    void skill1(Team& myTeam, Team& enemyTeam) override;
    void skill2(Team& myTeam, Team& enemyTeam) override;
    void specialSkill(Team& myTeam, Team& enemyTeam) override;

    string getRole() const override;
};

#endif