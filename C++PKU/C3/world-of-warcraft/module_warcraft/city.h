#ifndef CITY_H
#define CITY_H

#include <string>
#include "time.h"

class Warrior;

class City {
protected:
    int id;
    std::string flag;  // "None", "red", "blue"
    int LifeValue;
    City *next;
    City *prior;
    friend class Warrior;
public:
    Warrior *redWarrior;
    Warrior *blueWarrior;
    std::string lastWinner;
    City();
    virtual ~City(); // virtual destructor declaration.
    void init(int i, City *p, City *n);
    void produceLifeValue();
    void printMove();
    void Fight();
    void set_flag(std::string flag);
    int get_id();
    std::string get_flag();
    Warrior* get_red();
    Warrior* get_blue();
    virtual int get_numOfInvader();  // 主要给司令部使用
};

#endif // CITY_H
