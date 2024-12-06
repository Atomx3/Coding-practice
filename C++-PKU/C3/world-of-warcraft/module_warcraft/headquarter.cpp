#include "headquarter.h"
#include "warrior.h"
#include <iostream>

Headquarter::Headquarter(std::string a) : alliance(a) {
    std::fill(std::begin(warrior), std::end(warrior), nullptr);
}

void Headquarter::init(int lv, int po[]) {
    invader = nullptr;
    numOfWarrior = 0;
    numOfInvader = 0;
    LifeValue = lv;
    for (int i = 0; i < 5; i++) {
        ProduceOrder[i] = po[i];
    }
}

Headquarter::~Headquarter() {
    for (int i = 0; i < numOfWarrior; i++) {
        if (warrior[i]) {
            delete warrior[i];
        }
    }
}

std::string Headquarter::get_alliance() {
    return alliance;
}

int Headquarter::get_LifeValue() {
    return LifeValue;
}

int Headquarter::get_numOfWarrior() {
    return numOfWarrior;
}

// Headquarter 类其他成员函数的实现，包括 makeWarrior, award, reportElements 等。
