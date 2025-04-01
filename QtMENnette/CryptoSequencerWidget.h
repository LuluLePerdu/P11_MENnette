#pragma once
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QLabel>
#include "CryptoSequencer.h"


class CryptoSequencerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CryptoSequencerWidget(QWidget* parent = nullptr);
    ~CryptoSequencerWidget();

protected:
    //void paintEvent(QPaintEvent* event) override;
    //void keyPressEvent(QKeyEvent* event) override;
    void updateGame();

private:
    CryptoSequencer logic;
    QTimer* gameTimer;
    QLabel* label;

};