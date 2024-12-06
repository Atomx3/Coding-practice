#ifndef WARRIOR_H
#define WARRIOR_H

#include <string>
#include "time.h"

class Headquarter;
class City;

class Warrior {
protected:
    Headquarter *hq;
    City *pCity;
    int id;
    int strength;
    int attack;
    int weapon[3];
    static const std::string weaponName[3];
    std::string classes;   // 战士类别："dragon","ninja","iceman","lion","wolf"
    int classesID;    // 战士类别编号：0-4
    friend class Headquarter;
    friend std::ostream& operator<<(std::ostream &o, const Warrior *w);
public:
    bool win;
    static std::string warriorClasses[5];  // 各种战士的名称
    static int initialStrength[5];    // 初始生命值
    static int initialAttack[5];      // 初始攻击力
    Warrior();
    virtual ~Warrior();  
    Warrior(Headquarter *hq, int id, int s, int atk, int cid);
    virtual void printBornMessage();
    virtual void Attack(Warrior *enemy);
    virtual void FightBack(Warrior *enemy);
    virtual void putArrow(Warrior *enemy);
    virtual void bomb(Warrior *enemy);
    virtual void Hurt(Warrior *enemy, int atk);
    virtual void earn_elements();
    virtual void ReportWeapon();
    virtual void move();
    virtual void escape();
    virtual void yell();
    virtual void disarm(Warrior *enemy);
    void setWeapon(int kind);
    void set_strength(int s);
    int get_strength();
    int get_weapon(int i);
    int get_attack();
};

#endif // WARRIOR_H
