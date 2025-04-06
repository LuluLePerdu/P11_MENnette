#pragma once
#include <QWidget>
#include <QTimer>
#include <QLabel>

#include "CryptoSequencer.h"
#include <QGraphicsOpacityEffect>
#include <QErrorMessage>

class CryptoSequencer;


class CryptoSequencerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CryptoSequencerWidget(QWidget* parent = nullptr, int range=50);
    ~CryptoSequencerWidget();
	void repositionLabels();

signals:
	void timePenalty(int penalty);
	void returnToMenuRequested();

protected:
    void updateGame();
	void resizeEvent(QResizeEvent* event) override;

private:
    QTimer* gameTimer;
    QLabel* label;
    QLabel* labelT1;
	QLabel* labelT2;
	QLabel* labelB1;
	QLabel* labelB2;
	QLabel* labelResult;
    CryptoSequencer* logic;
    

	//SnakeMaze* snakeMaze;
};