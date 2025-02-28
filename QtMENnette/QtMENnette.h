#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtMENnette.h"

class QtMENnette : public QWidget
{
    Q_OBJECT

public:
    QtMENnette(QWidget *parent = nullptr);
    ~QtMENnette();

private:
    Ui::QtMENnetteClass ui;
};
