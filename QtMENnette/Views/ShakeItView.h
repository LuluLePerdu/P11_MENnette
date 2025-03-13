#pragma once
#include <map>
#include <string>
#include <iostream>
#include "ShakeItModel.h"
#include "ui_QtMENnette.h"
#include <QWidget>
#include <QKeyEvent>
#include <QProgressBar>
#include <QFocusEvent>
#include <QTimer>  

using namespace std;

class ShakeItView : public QWidget
{
    Q_OBJECT
public:
    explicit ShakeItView(QWidget* parent = nullptr);
    void render(ShakeItModel& model);
    void link(ShakeItModel* model);

signals:
    void keyPressed(QKeyEvent* event);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void focusInEvent(QFocusEvent* event) override; 

private:
    Ui::QtMENnetteClass ui;
    ShakeItModel* model = nullptr;
};
