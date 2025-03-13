#include "stdafx.h"
#include "QtMENnette.h"
#include <QtWidgets/QApplication>
#include <qtimer.h>

#include "ShakeItController.h"
#include "ShakeItView.h"
#include <QDebug>



QtMENnette* QtMENnette::w = NULL;

int main(int argc, char *argv[])
{
	// ! Pas touche
    QApplication a(argc, argv);
	a.setStyle(QStyleFactory::create("Fusion"));	// * Force le style des widgets a etre de la meme apparence que celle dans QtDesigner

	QtMENnette* w = QtMENnette::instance();

	ShakeItView shakeItView;
	ShakeItController shakeItController(shakeItView);

	//loop qui repart a chaque 33ms
	QTimer timer;
	QObject::connect(&timer, &QTimer::timeout, [&]() {
		
		shakeItController.run();
		
		}); //fin loop
	timer.start(33);

	// ! Pas touche
    //w->show();
	shakeItView.show();  // Assurez-vous que ShakeItView est aussi affich�e
	shakeItView.setFocus();
    return a.exec();
}
