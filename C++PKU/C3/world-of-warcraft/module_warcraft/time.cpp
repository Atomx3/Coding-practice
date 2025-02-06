#include "time.h"

Time gameTime(0, 0);

Time::Time(int h, int m) : hour(h), minute(m) {}

void Time::init(int h, int m) {
    hour = h;
    minute = m;
}

void Time::updateTime() {
    minute++;
    if (minute == 60) {
        hour++;
        minute = 0;
    }
}

std::ostream& operator<<(std::ostream &o, const Time &t) {
    o << std::setw(3) << std::setfill('0') << t.hour << ":" << std::setw(2) << t.minute;
    return o;
}
