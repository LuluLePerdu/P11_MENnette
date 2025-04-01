#include "CryptoSequencerWidget.h"

CryptoSequencerWidget::CryptoSequencerWidget(QWidget* parent) :
    QWidget(parent),
    gameTimer(new QTimer(this))
{
    logic.initialize();

    connect(gameTimer, &QTimer::timeout, this, &CryptoSequencerWidget::updateGame);
    gameTimer->start(100);

    setFixedSize(500, 500);
    label->setText("Initial Text");
    label->setGeometry(10, 10, 200, 50);
}

CryptoSequencerWidget::~CryptoSequencerWidget()
{
}

void CryptoSequencerWidget::updateGame()
{
    /*logic.movePlayer();
    logic.updateTimer();
    if (!logic.inGame()) {
        gameTimer->stop();
    }*/
	string a = logic.updateSequence();
    label->setText(QString::fromStdString(a));

    update();
}