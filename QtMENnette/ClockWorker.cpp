#include "ClockWorker.h"

ClockWorker::ClockWorker(QObject* parent) : QObject(parent)
{
    timer.setInterval(1000);
    connect(&timer, &QTimer::timeout, this, &ClockWorker::updateTime);
}

void ClockWorker::start()
{
    remainingSeconds = countdown.minute() * 60 + countdown.second();
    timer.start();
}

void ClockWorker::stop()
{
    timer.stop();
}

void ClockWorker::addPenalty(int seconds)
{
    penaltySeconds += seconds;
}

void ClockWorker::setCountdown(int minutes, int seconds)
{
    countdown = QTime(0, minutes, seconds);
    remainingSeconds = minutes * 60 + seconds;
}

void ClockWorker::updateTime()
{
    remainingSeconds--;

    if (penaltySeconds > 0) {
        int penaltyToApply = qMin(penaltySeconds, 5); 
        remainingSeconds -= penaltyToApply;
        penaltySeconds -= penaltyToApply;
    }

    if (remainingSeconds <= 0) {
        emit timeExpired();
        return;
    }

    QTime displayTime(0, 0, 0);
    displayTime = displayTime.addSecs(remainingSeconds);
    emit timeUpdated(displayTime.toString("mm:ss"));
}