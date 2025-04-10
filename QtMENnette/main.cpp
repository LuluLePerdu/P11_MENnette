#include "stdafx.h"
#include <QDebug>
#include <QtWidgets/QApplication>
#include <qtimer.h>

#include "MainWindow.h"
#include "SimonSays.h"
#include "CryptoSequencer.h"

MainWindow* MainWindow::w = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.setStyle(QStyleFactory::create("Fusion"));/// Force le style des widgets à être de la même apparence que celle dans QtDesigner

	MainWindow* w = MainWindow::instance();

	w->showFullScreen();
    return a.exec();
}
