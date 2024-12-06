#include "warrior.h"
#include "city.h"
#include "headquarter.h"
#include <iostream>
#include <iomanip>
#include <cmath>

extern int numOfCity;
extern int arrow_atk;
extern int loyalty_loss;

std::string Warrior::warriorClasses[5] = { "dragon","ninja","iceman","lion","wolf" };
int Warrior::initialStrength[5] = { 0 };
int Warrior::initialAttack[5] = { 0 };
const std::string Warrior::weaponName[3] = { "sword","bomb","arrow" };

Warrior::Warrior() {}
Warrior::~Warrior() {}

Warrior::Warrior(Headquarter *hq, int id, int s, int atk, int cid)
    : hq(hq), id(id), strength(s), attack(atk), classesID(cid), win(false) {
    classes = warriorClasses[classesID];
    std::fill(std::begin(weapon), std::end(weapon), 0);
}

void Warrior::printBornMessage() {
    std::cout << gameTime << " " << this << " born" << std::endl;
}

void Warrior::setWeapon(int kind) {
    if (kind == 0) {
        weapon[0] = static_cast<int>(attack * 0.2);
    } else if (kind == 1) {
        weapon[1] = 1;
    } else {
        weapon[2] = 3;
    }
}

void Warrior::set_strength(int s) {
    strength = s;
}

int Warrior::get_strength() {
    return strength;
}

int Warrior::get_weapon(int i) {
    return weapon[i];
}

int Warrior::get_attack() {
    return attack;
}

// Warrior 类其他成员函数的实现，包括 Attack, FightBack, Hurt 等等。
// 这些函数可能会涉及到其他类，需要确保相关头文件的包含和依赖关系的处理。
