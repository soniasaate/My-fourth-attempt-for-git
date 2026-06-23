#ifndef DOCTOR_WHITE_H
#define DOCTOR_WHITE_H

#include "Hero.h"

class DoctorWhite : public Hero
{
public:
    DoctorWhite();

    void skill1(Team& myTeam, Team& enemyTeam) override;
    void skill2(Team& myTeam, Team& enemyTeam) override;
    void specialSkill(Team& myTeam, Team& enemyTeam) override;

    string getRole() const override;
};

#endif