#include "city.h"
#include "warrior.h"
#include "headquarter.h"
#include <iostream>

extern int numOfCity;
extern Headquarter red;
extern Headquarter blue;
extern bool GameOver;
extern int loyalty_loss;
extern int arrow_atk;

City::City() {}

City::~City() {}

void City::init(int i, City *p, City *n) {
    id = i;
    flag = "None";
    LifeValue = 0;
    redWarrior = nullptr;
    blueWarrior = nullptr;
    lastWinner = "None";
    next = n;
    prior = p;
}

void City::produceLifeValue() {
    LifeValue += 10;
}

void City::set_flag(std::string flag) {
    this->flag = flag;
    std::cout << gameTime << " " << flag << " flag raised in city " << id << std::endl;
}

int City::get_id() {
    return id;
}

std::string City::get_flag() {
    return flag;
}

Warrior* City::get_red() {
    return redWarrior;
}

Warrior* City::get_blue() {
    return blueWarrior;
}

int City::get_numOfInvader() {
    return 0;
}

void City::printMove() {
    if (id == 0 && blueWarrior) {
        std::cout << gameTime << " " << blueWarrior << " reached red headquarter with "
                  << blueWarrior->get_strength() << " elements and force " 
                  << blueWarrior->get_attack() << std::endl;
        if (red.numOfInvader == 2) {
            std::cout << gameTime << " red headquarter was taken" << std::endl;
            GameOver = true;
        }
    } else if (id == numOfCity + 1 && redWarrior) {
        std::cout << gameTime << " " << redWarrior << " reached blue headquarter with "
                  << redWarrior->get_strength() << " elements and force "
                  << redWarrior->get_attack() << std::endl;
        if (blue.numOfInvader == 2) {
            std::cout << gameTime << " blue headquarter was taken" << std::endl;
            GameOver = true;
        }
    } else {
        if (redWarrior) {
            std::cout << gameTime << " " << redWarrior << " marched to city " << id;
        }
    }
}