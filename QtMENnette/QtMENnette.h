#pragma once

//#include <QtWidgets/QWidget>
#include <QtWidgets/qmainwindow.h>
#include "ui_QtMENnette.h"


class QtMENnette : public QMainWindow {
    Q_OBJECT

public:
    QtMENnette(QMainWindow* parent = nullptr);
	~QtMENnette();
    static QtMENnette* instance();

private:
    static QtMENnette* w;
    Ui::QtMENnetteClass ui;

};


