#include "CryptoSequencerWidget.h"

CryptoSequencerWidget::CryptoSequencerWidget(QWidget* parent, int range) :
    QWidget(parent),
    gameTimer(new QTimer(this)),
    label(new QLabel(this)),
    labelT1(new QLabel(this)),
    labelT2(new QLabel(this)),
    labelB1(new QLabel(this)),
    labelB2(new QLabel(this)),
	labelResult(new QLabel(this)),
    logic(new CryptoSequencer(range))
{
    connect(gameTimer, &QTimer::timeout, this, &CryptoSequencerWidget::updateGame);
    gameTimer->start(100);

    // Set fonts and styles
    label->setFont(QFont("Cascadia Code", 100));
    label->setText("1234567890");
    label->setAlignment(Qt::AlignCenter);
	label->setStyleSheet("QLabel { color: rgb(51, 204, 204);}");

    labelT1->setFont(QFont("Cascadia Code", 70));
    labelT1->setText("1234567890");
    labelT1->setStyleSheet("QLabel{ color: rgba(51, 204, 204, 0.65);}");
    labelT1->setAlignment(Qt::AlignCenter);

    labelT2->setFont(QFont("Cascadia Code", 85));
    labelT2->setText("1234567890");
    labelT2->setStyleSheet("QLabel{ color: rgba(51, 204, 204, 0.85);}");
    labelT2->setAlignment(Qt::AlignCenter);

    labelB1->setFont(QFont("Cascadia Code", 85));
    labelB1->setText("1234567890");
    labelB1->setStyleSheet("QLabel{ color: rgba(51, 204, 204, 0.85);}");
    labelB1->setAlignment(Qt::AlignCenter);

    labelB2->setFont(QFont("Cascadia Code", 70));
    labelB2->setText("1234567890");
    labelB2->setStyleSheet("QLabel{ color: rgba(51, 204, 204, 0.65);}");
    labelB2->setAlignment(Qt::AlignCenter);

	labelResult->setFont(QFont("Cascadia Code", 70));
    labelResult->setText("eENTER CODE");
    labelResult->setStyleSheet("QLabel { color: rgb(255, 165, 0); }"); 
    labelResult->setAlignment(Qt::AlignCenter);


    // Position labels on widget resize
    repositionLabels();
}

CryptoSequencerWidget::~CryptoSequencerWidget()
{
    if (gameTimer) {
        gameTimer->stop();
    }
	delete gameTimer;
	delete label;
	delete labelT1;
	delete labelT2;
	delete labelB1;
	delete labelB2;
	delete labelResult;
	delete logic;
}

void CryptoSequencerWidget::updateGame()
{
	if (logic->isGameOver()) {
		gameTimer->stop();
		QMessageBox msg;
		msg.setWindowTitle("Cryptographic Sequencer");
		msg.setText("GAME COMPLETED!");
		//msg.setIcon(QMessageBox::Information);
		//msg.setStandardButtons(QMessageBox::Ok);
		msg.exec();

		return;
	}
    if (logic->wrongCode) {
		logic->wrongCode = false;
		emit timePenalty(20);
    }
    std::string a = logic->updateSequence();
    label->setText(QString::fromStdString(a));
    labelT1->setText(QString::fromStdString(logic->randomizeString(a, 0.4)));
    labelT2->setText(QString::fromStdString(logic->randomizeString(a, 0.15)));
    labelB1->setText(QString::fromStdString(logic->randomizeString(a, 0.15)));
    labelB2->setText(QString::fromStdString(logic->randomizeString(a, 0.4)));
	labelResult->setText(QString::fromStdString(logic->getUserCode()));

}

void CryptoSequencerWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    repositionLabels();
}

void CryptoSequencerWidget::repositionLabels()
{
    int labelWidth = 800;
    int labelHeigth = 110;
    //int labelHeigth = 120;
    int padding = 20;

    int totalHeight = labelHeigth + labelHeigth * 4;
    int startY = (height() - totalHeight) / 2 - 100;

    if (startY < padding) {
        startY = padding;
    }

    labelT1->setGeometry(width() / 2 - labelWidth / 2, startY, labelWidth, labelHeigth);

    labelT2->setGeometry(width() / 2 - labelWidth / 2, startY + labelHeigth, labelWidth, labelHeigth);

    label->setGeometry(width() / 2 - labelWidth / 2, startY + labelHeigth * 2, labelWidth, labelHeigth);

    labelB1->setGeometry(width() / 2 - labelWidth / 2, startY + labelHeigth * 2 + labelHeigth, labelWidth, labelHeigth);

    labelB2->setGeometry(width() / 2 - labelWidth / 2, startY + labelHeigth * 3 + labelHeigth, labelWidth, labelHeigth);

    int resultY = height() - 100 - 120;  

    //pas moi ca en bas
    if (resultY < startY + labelHeigth * 4 + labelHeigth + padding) {
        resultY = startY + labelHeigth * 4 + labelHeigth + padding;
    }

    labelResult->setGeometry(width() / 2 - labelWidth / 2,
        resultY,
        labelWidth, 100);
}