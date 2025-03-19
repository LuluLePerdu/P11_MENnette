#pragma once
#include <chrono>

class Clock {
public:
    using clock_type = std::chrono::high_resolution_clock;
    using time_point = std::chrono::time_point<clock_type>;
    using duration = std::chrono::duration<double>;

    Clock();

    void start(); // D�marrer l'horloge
    void restart(); // Red�marrer l'horloge
    double getElapsedTime() const; // Obtenir le temps �coul� en secondes
    double getDeltaTime(); // Obtenir le temps �coul� depuis le dernier appel � getDeltaTime

private:
    time_point startTime;
    time_point lastTime;
};