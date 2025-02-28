#include "stdafx.h"
#include "QtMENnette.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtMENnette w;
    w.show();
    return a.exec();
}
