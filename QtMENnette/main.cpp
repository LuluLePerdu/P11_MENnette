#include "stdafx.h"
#include <QDebug>
#include <QtWidgets/QApplication>
#include <qtimer.h>
#include <QDebug>

#include "MainWindow.h"
#include "SimonSays.h"
#include "CryptoSequencer.h"



MainWindow* MainWindow::w = NULL;

int main(int argc, char *argv[])
{
	// ! Pas touche
    QApplication a(argc, argv);
	a.setStyle(QStyleFactory::create("Fusion"));	// * Force le style des widgets a etre de la meme apparence que celle dans QtDesigner

	MainWindow* w = MainWindow::instance();



	//loop qui repart a chaque 33ms
	QTimer timer;
	QObject::connect(&timer, &QTimer::timeout, [&]() {
		
		}); 
	timer.start(33);

	// ! Pas touche
    w->show();
    return a.exec();
}
