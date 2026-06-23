#ifndef HERO_H
#define HERO_H  
#include <iostream>
using namespace std;


class hero
{
protected:
    string name;
    int hp;
    int maxHp;

    int specialCooldown;      // محدودیت حرکت ویژه
    int turnsSinceSpecial;    // چند نوبت از اخرین حرکت ویژه گذشته

    bool alive;

public:
    hero(); //constracter
    virtual void skill1(...) = 0;
    virtual void skill2(...) = 0;
    virtual void specialSkill(...) = 0;

    virtual string getRole() = 0;

    void takeDamage(int damage);
    void heal(int amount);

    bool isAlive() const;
    int getHP() const; //گرفتن عدد جون

    bool canUseSpecial(); // بررسی ایا میشه قدرت ویژه انتخاب کرد

    void increaseturnsp(); //هر نوبت که قدرت ویژه استفاده نشد میشماره
    void resetturnspr(); //هروقت استفاده شد صفرش میکنه

    virtual ~hero();
};


#endif