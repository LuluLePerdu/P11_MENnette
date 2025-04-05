#pragma once

#include <QObject>
#include <QTimer>
#include <QTime>

class ClockWorker : public QObject
{
    Q_OBJECT
public:
    explicit ClockWorker(QObject* parent = nullptr);

public slots:
    void start();
    void stop();
    void addPenalty(int seconds);
    void setCountdown(int minutes, int seconds);

signals:
    void timeUpdated(const QString& timeString);
    void timeExpired();

private slots:
    void updateTime();

private:
    QTimer timer;
    QTime countdown;
    int remainingSeconds;
    int penaltySeconds = 0;
};