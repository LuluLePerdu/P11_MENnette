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

    setFixedSize(5000, 500);
	label->setFont(QFont("Cascadia Code", 100));
    label->setText("1234567890");
	//label->setStyleSheet("QLabel { background-color : black; }");



}


CryptoSequencerWidget::~CryptoSequencerWidget()
{
}

void CryptoSequencerWidget::updateGame()
{
    std::string a = logic->updateSequence(); 
    label->setText(QString::fromStdString(a));
}