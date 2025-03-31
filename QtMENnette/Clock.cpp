#include "Clock.h"

Clock::Clock() {
    start();
}

void Clock::start() {
    startTime = clock_type::now();
    lastTime = startTime;
}

void Clock::restart() {
    start();
}

double Clock::getElapsedTime() const {
    auto now = clock_type::now();
    return std::chrono::duration_cast<duration>(now - startTime).count();
}

double Clock::getDeltaTime() {
    auto now = clock_type::now();
    auto delta = std::chrono::duration_cast<duration>(now - lastTime).count();
    lastTime = now;
    return delta;
}