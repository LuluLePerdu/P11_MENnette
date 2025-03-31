#pragma once
#include <chrono>

class Clock {
public:
    using clock_type = std::chrono::high_resolution_clock;
    using time_point = std::chrono::time_point<clock_type>;
    using duration = std::chrono::duration<double>;

    Clock();

    void start(); // Démarrer l'horloge
    void restart(); // Redémarrer l'horloge
    double getElapsedTime() const; // Obtenir le temps écoulé en secondes
    double getDeltaTime(); // Obtenir le temps écoulé depuis le dernier appel à getDeltaTime

private:
    time_point startTime;
    time_point lastTime;
};