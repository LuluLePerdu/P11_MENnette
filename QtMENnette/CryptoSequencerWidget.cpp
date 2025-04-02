#include "CryptoSequencerWidget.h"

CryptoSequencerWidget::CryptoSequencerWidget(QWidget* parent) :
    QWidget(parent),
    gameTimer(new QTimer(this)),
    label(new QLabel(this)),
    logic(new CryptoSequencer())
{
    //logic->initialize(); 

    connect(gameTimer, &QTimer::timeout, this, &CryptoSequencerWidget::updateGame);
    gameTimer->start(100);

    setFixedSize(500, 500);
    label->setText("alloi");
    label->setGeometry(10, 10, 200, 50);
}


CryptoSequencerWidget::~CryptoSequencerWidget()
{
}

void CryptoSequencerWidget::updateGame()
{
    /*std::string a = logic->updateSequence(); 
    label->setText(QString::fromStdString(a));
	QErrorMessage msg;
	msg.showMessage(QString::fromStdString(a));
	msg.exec();

    update();*/
}