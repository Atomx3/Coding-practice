#ifndef HEADQUARTER_H
#define HEADQUARTER_H

#include "city.h"

class Headquarter : public City {
private:
    std::string alliance;   // "red", "blue"
    int numOfWarrior;
    int ProduceOrder[5];
    Warrior *warrior[1000];
    friend class Warrior;
    friend std::ostream& operator<<(std::ostream &o, const Warrior *w);
public:
    Warrior *invader;
    int numOfInvader;
    Headquarter(std::string a);
    virtual ~Headquarter();
    void init(int lv, int po[]);
    void makeWarrior();
    void award(Warrior *w);
    void reportElements();
    std::string get_alliance();
    int get_LifeValue();
    int get_numOfWarrior();
};

#endif // HEADQUARTER_H
