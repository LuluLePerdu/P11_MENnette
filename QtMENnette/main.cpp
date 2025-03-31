#include "stdafx.h"
#include <QDebug>
#include <QtWidgets/QApplication>
#include <qtimer.h>
#include <QDebug>

#include "MainWindow.h"
#include "SimonSays.h"
#include "CryptographicSequencer.h"



MainWindow* MainWindow::w = NULL;

int main(int argc, char *argv[])
{
	// ! Pas touche
    QApplication a(argc, argv);
	a.setStyle(QStyleFactory::create("Fusion"));	// * Force le style des widgets a etre de la meme apparence que celle dans QtDesigner

	MainWindow* w = MainWindow::instance();


	CryptographicSequencer* cs = new CryptographicSequencer();
	QObject::connect(w->getUI()->btnPoten, &QPushButton::clicked, [cs, w]() {
		cs->playPot(w->getUI()->labPotSequence);
		});

	//loop qui repart a chaque 33ms
	QTimer timer;
	QObject::connect(&timer, &QTimer::timeout, [&]() {
		
		}); 
	timer.start(33);

	// ! Pas touche
    w->show();
	//shakeItView.show();  // Assurez-vous que ShakeItView est aussi affichée
	//shakeItView.setFocus();
    return a.exec();
}
