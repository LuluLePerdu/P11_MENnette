#include "ThreadCutterWidget.h"

ThreadCutterWidget::ThreadCutterWidget(QWidget* parent) : QWidget(parent) 
{
	gameTimer = new QTimer(this);
	labIns = new QLabel(this);
	labRes = new QLabel(this);
	labDebug = new QLabel(this);

	connect(gameTimer, &QTimer::timeout, this, [this]() {
		logic.run();
		labDebug->setText(QVariant(logic.getCompleted()).toString());
		checkEnd();
		});

	labIns->setGeometry(50, 200, 700, 300);
	labDebug->setGeometry(100, 0, 100, 100);

	labIns->setVisible(true);
	labRes->setVisible(false);

	startGame();
}

ThreadCutterWidget::~ThreadCutterWidget() {
	logic.turnOffLed();
}

void ThreadCutterWidget::startGame() {
	/*
	renderText(labIns, QString::fromLatin1("Si la DEL verte et 2 autres DELs sont allum�es, appuyez sur le bouton vert."
		"\n\nSinon, si la DEL verte et la DEL rouge sont allum�es mais aucune autre, appuyez sur le bouton rouge."
		"\n\nSinon, si les 4 DELs sont allum�es, appuyez sur le bouton rouge."
		"\n\nSinon, si les 4 DELs sont �teintes, appuyez sur le bouton la plus � droite."
		"\n\nSinon, si la DEL bleue et la DEL jaune sont allum�es mais aucune autre, appuyez sur le bouton jaune."
		"\n\nSinon, si uniquement la DEL rouge est allum�e, appuyez sur le bouton le plus � gauche."
		"\n\nSinon, si aucune des autres conditions n'est remplie mais que 2 DELs sont allum�es, appuyez sur le bouton rouge."
		"\n\nSinon, appuyez sur le deuxi�me bouton � partir de la gauche."
		"\n\nSi vous voyez un interrupteur sur lequel l'inscription \'NE PAS ACTIVER\' est inscrite, il ne faudrait peut-�tre pas l'activer..."));
	*/
	
	logic.turnOffLed();
	logic.render();

	gameTimer->start(10);
}

void ThreadCutterWidget::checkEnd() {
	//if (logic.getCompleted() != 2) {
		//QString output;
		gameTimer->stop();
		logic.turnOffLed();

		if (logic.getCompleted() == 0) {
			//output = QString::fromLatin1("Module d�samorc� !");
			QMessageBox msg;
			msg.setWindowTitle("LED GAME");
			msg.setText("GAME COMPLETED!");
			msg.exec();
			emit returnToMenuRequested(true);

		}
		else {
			//output = QString::fromLatin1("Mauvais bouton !");
			QMessageBox msg;
			msg.setWindowTitle("LED GAME");
			msg.setText("WRONG LED!");
			msg.exec();
			emit timePenalty(timeOnLoss);
			emit returnToMenuRequested(false);
		}

		//renderText(labRes, output);

		
	//}
}

void ThreadCutterWidget::renderText(QLabel* label, QString text) {
	label->setText(text);
	label->setVisible(true);
}