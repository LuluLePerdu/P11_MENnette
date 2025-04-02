#pragma once
#include <QWidget>
#include <QTimer>
#include <QLabel>

#include "CryptoSequencer.h"
#include "SnakeMaze.h"

#include <QErrorMessage>

class CryptoSequencer;


class CryptoSequencerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CryptoSequencerWidget(QWidget* parent = nullptr);
    ~CryptoSequencerWidget();

protected:
    void updateGame();

private:
    QTimer* gameTimer;
    QLabel* label;
    CryptoSequencer* logic;
	//SnakeMaze* snakeMaze;
};