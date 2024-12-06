#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>

class Time {
public:
    int hour;
    int minute;
    Time(int h = 0, int m = 0);
    void init(int h, int m);
    void updateTime();
    friend std::ostream& operator<<(std::ostream &o, const Time &t);
};

extern Time gameTime;

#endif // TIME_H
