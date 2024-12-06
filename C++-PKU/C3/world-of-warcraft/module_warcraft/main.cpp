#include <iostream>
#include "time.h"
#include "city.h"
#include "warrior.h"
#include "headquarter.h"

// 全局变量
int redOrder[5] = {2, 3, 4, 1, 0};
int blueOrder[5] = {3, 0, 1, 2, 4};
int TOTALTIME = 0;
int arrow_atk;
int loyalty_loss;
int initialLifeValue, numOfCity;
bool GameOver = false;

Headquarter red("red"), blue("blue");

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int numOfTest = 0;
    std::cin >> numOfTest;

    for (int i = 1; i <= numOfTest; i++) {
        // 初始化全局变量
        gameTime.init(0, 0);
        GameOver = false;

        // 输入参数
        std::cin >> initialLifeValue >> numOfCity >> arrow_atk >> loyalty_loss >> TOTALTIME;
        for (int j = 0; j < 5; j++) {
            std::cin >> Warrior::initialStrength[j];
        }
        for (int j = 0; j < 5; j++) {
            std::cin >> Warrior::initialAttack[j];
        }

        // 初始化司令部和城市
        City* city[22];   // 为了避免越界，数组大小取足够大
        for (int j = 1; j <= numOfCity; j++) {
            city[j] = new City;
        }
        city[0] = &red;
        city[numOfCity + 1] = &blue;
        for (int j = 1; j <= numOfCity; j++) {
            city[j]->init(j, city[j - 1], city[j + 1]);
        }
        city[0]->init(0, nullptr, city[1]);
        city[numOfCity + 1]->init(numOfCity + 1, city[numOfCity], nullptr);
        // 一定要先调用 City 的 init 再调用 Headquarter 的 init
        red.init(initialLifeValue, redOrder);
        blue.init(initialLifeValue, blueOrder);

        // 开始游戏
        std::cout << "Case " << i << ":" << std::endl;
        while (true) {
            if (gameTime.minute == 0) {
                red.makeWarrior();
                blue.makeWarrior();
            }
            if (gameTime.minute == 5) {  // 狮子逃跑
                for (int j = 0; j <= numOfCity + 1; j++) {
                    if (city[j]->get_red()) {
                        city[j]->get_red()->escape();
                    }
                    if (city[j]->get_blue()) {
                        city[j]->get_blue()->escape();
                    }
                }
            }
            if (gameTime.minute == 10) {  // 武士前进
                // 为了防止前进的信息丢失，前进顺序相反
                for (int j = numOfCity + 1; j >= 0; j--) {
                    if (city[j]->get_red()) {
                        city[j]->get_red()->move();
                    }
                }
                for (int j = 0; j <= numOfCity + 1; j++) {
                    if (city[j]->get_blue()) {
                        city[j]->get_blue()->move();
                    }
                }
                for (int j = 0; j <= numOfCity + 1; j++) {
                    city[j]->printMove();
                }
                if (GameOver) {
                    break;
                }
            }
            if (gameTime.minute == 20) {  // 城市产出生命元
                for (int j = 1; j <= numOfCity; j++) {
                    city[j]->produceLifeValue();
                }
            }
            if (gameTime.minute == 30) {  // 武士获取生命元
                for (int j = 1; j <= numOfCity; j++) {
                    if (city[j]->get_red() && !city[j]->get_blue()) {
                        city[j]->get_red()->earn_elements();
                    } else if (!city[j]->get_red() && city[j]->get_blue()) {
                        city[j]->get_blue()->earn_elements();
                    }
                }
            }
            if (gameTime.minute == 35) {  // 放箭
                for (int j = 1; j <= numOfCity; j++) {
                    Warrior* redWarrior = city[j]->get_red();
                    Warrior* blueWarrior = city[j]->get_blue();
                    if (redWarrior) {
                        redWarrior->putArrow(city[j + 1]->get_blue());
                    }
                    if (blueWarrior) {
                        blueWarrior->putArrow(city[j - 1]->get_red());
                    }
                }
            }
            if (gameTime.minute == 38) {  // 使用炸弹
                for (int j = 1; j <= numOfCity; j++) {
                    if (city[j]->get_red()) {
                        city[j]->get_red()->bomb(city[j]->get_blue());
                    }
                    if (city[j]->get_blue()) {
                        city[j]->get_blue()->bomb(city[j]->get_red());
                    }
                }
            }
            if (gameTime.minute == 40) {  // 战斗
                for (int j = 1; j <= numOfCity; j++) {
                    city[j]->Fight();
                }
                for (int j = 1; j <= numOfCity; j++) {  // 奖励顺序
                    red.award(city[j]->redWarrior);
                    blue.award(city[numOfCity - j + 1]->blueWarrior);
                }
            }
            if (gameTime.minute == 50) {  // 司令部报告生命元
                red.reportElements();
                blue.reportElements();
            }
            if (gameTime.minute == 55) {  // 武士报告武器
                for (int j = 0; j <= numOfCity + 1; j++) {
                    if (city[j]->get_red()) {
                        city[j]->get_red()->ReportWeapon();
                    }
                }
                if (blue.invader) {   // 到达对方司令部的武士也要报告
                    blue.invader->ReportWeapon();
                }
                if (red.invader) {
                    red.invader->ReportWeapon();
                }
                for (int j = 0; j <= numOfCity + 1; j++) {
                    if (city[j]->get_blue()) {
                        city[j]->get_blue()->ReportWeapon();
                    }
                }
            }

            gameTime.updateTime();
            if (60 * gameTime.hour + gameTime.minute > TOTALTIME) {
                break;
            }
        }

        // 清理动态分配的内存
        for (int j = 1; j <= numOfCity; j++) {
            if (city[j]) {
                delete city[j];
            }
        }
    }
    return 0;
}